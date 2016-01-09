#include "utils.h"
#include "stype.h"


int parse_entry(char* fn, ledger_entry *entry) {
    int bytes_read;
    size_t buffer_size = BUFFER_SIZE;
    char *buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    char *label = NULL;
    double value;
    FILE *fp = fopen(fn, "r");

    if (fp == NULL) {
        printf("open error: %s\n", fn);
        return -1;
    }

    if ((bytes_read = getline(&buffer, &buffer_size, fp)) <= 0) {
        printf("parse error 0: %s\n", fn);
        free(buffer);
        fclose(fp);
        return -1;
    }
    // entry->size = strtol(buffer, NULL, 10);
    entry->size = 0;
    if ((bytes_read = getline(&buffer, &buffer_size, fp)) <= 0) {
        puts("parse error 1.\n");
        free(buffer);
        fclose(fp);
        return -1;
    }
    // entry->total = strtof(buffer, NULL);
    entry->total = 0;
    if ((bytes_read = getline(&buffer, &buffer_size, fp)) <= 0) {
        puts("parse error 2.\n");
        free(buffer);
        fclose(fp);
        return -1;
    }
    entry->t = strtol(buffer, NULL, 10);
    // entry->t = time(NULL);
    entry->labels = NULL;
    entry->values = NULL;

    while((bytes_read = getline(&buffer, &buffer_size, fp)) > 0) {
        parse_line(buffer, &label, &value);
        add_entry(entry, label, value);
    }

    free(buffer);
    fclose(fp);

    return 0;
}


int parse_line(char *line, char **label, double *value) {
    *label = strtok(line, ",");
    *value = strtof(strtok(NULL, ","), NULL);
    return 0;
}


int merge_entry(ledger_entry *left, ledger_entry *right) {
    int i = 0, size = right->size;
    left->t = time(NULL);

    for (i = 0; i < size; ++i) {
        add_entry(left, right->labels[i], right->values[i]);
    }

    return 0;
}


int add_entry(ledger_entry *le, char *label, double value) {
    int idx = index_of_e(le, label);
    char *nl = NULL;

    if (le->labels == NULL || le->values == NULL) {
        le->labels = (char**)malloc(sizeof(char*));
        le->values = (double*)malloc(sizeof(double));
    }

    if (idx == -1) {
        nl = (char*)malloc(sizeof(char)*(strlen(label)+1));
        strcpy(nl, label);
        le->size += 1;
        le->labels = (char**)realloc(le->labels, le->size*sizeof(char*));
        le->values = (double*)realloc(le->values, le->size*sizeof(double));
        le->labels[le->size-1] = nl;
        le->values[le->size-1] = value;
    } else {
        le->values[idx] += value;
    }
    le->total += value;

    return 0;
}


int index_of_e(ledger_entry *le, char *label) {
    int i = 0;

    for(i = 0; i < le->size; ++i) {
        if (strcmp(le->labels[i], label) == 0) {
            return i;
        }
    }

    return -1;
}


int check_date(char *fn, char *backup) {
    char newpath[1024];
    time_t ttime = time(NULL); 
    struct tm *ttm = gmtime(&ttime);
    struct tm *etm = NULL;
    FILE *fp = NULL;
    ledger_entry entry;

    strcpy(newpath, backup);
    strcat(newpath, basename(fn));

    parse_entry(fn, &entry);
    etm = gmtime(&(entry.t));

    if (ttm->tm_mday == etm->tm_mday) {
        return 0;
    } else {
        rename(fn, newpath);
        fp = fopen(fn, "w");
        fprintf(fp, "0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0");
        return 1;
    }
}


int save_entry(char* fn, ledger_entry *entry) {
    int i = 0, size = entry->size;
    FILE *fp = fopen(fn, "w");

    fprintf(fp, "%d\n", entry->size);
    fprintf(fp, "%f\n", entry->total);
    fprintf(fp, "%ld\n", entry->t);

    for (i = 0; i < size; ++i) {
        fprintf(fp, "%s,%f\n", entry->labels[i], entry->values[i]);
    }

    fclose(fp);

    return 0;
}


void prepare_entry(int flag, ledger_entry *entry, int dayofyear) {
    int diff1 = 0, diff2 = 0, diff3 = 0;
    time_t tt = time(NULL);
    struct tm* ttm= gmtime(&tt), *ettm = NULL;
    char *datum_folder = "./datum/", buffer[BUFFER_SIZE];
    DIR *dirp = NULL;
    struct dirent *dp = NULL;
    ledger_entry tmpe;
    entry->t = 0;
    entry->size = 0;
    entry->total = 0;
    entry->labels = NULL;
    entry->values = NULL;

    if ((dirp = opendir(datum_folder)) == NULL) {
        printf("open dir error\n");
        return;
    }

    do {
        errno = 0;
        if ((dp = readdir(dirp)) != NULL) {
            if (dp->d_name[0] == '.') {
                continue;
            }
            strcpy(buffer, datum_folder);
            if ((parse_entry(strcat(buffer, dp->d_name), &tmpe) == -1)) {
                continue;
            }
            ettm = gmtime(&tmpe.t);

            switch (flag) {
                case 0:
                    if (ettm->tm_year == ttm->tm_year &&
                            ettm->tm_yday == dayofyear - 1) {
                        merge_entry(entry, &tmpe);
                    }
                    break;
                case 1:
                    diff1 = ettm->tm_wday - 0;
                    diff2 = 6 - ettm->tm_wday;
                    diff3 = abs(ettm->tm_year - ttm->tm_year);
                    if (diff3 < 7 && (diff3 < diff1 || diff3 < diff2)) {
                        merge_entry(entry, &tmpe);
                    }
                    break;
                case 2:
                    if (ettm->tm_year == ttm->tm_year &&
                            ettm->tm_mon == ttm->tm_mon) {
                        merge_entry(entry, &tmpe);
                    }
                    break;
                case 3:
                    if (ettm->tm_year == ttm->tm_year) {
                        merge_entry(entry, &tmpe);
                    }
                    break;
                default:
                    break;
            }

        }
    } while(dp != NULL);

    return;
}
