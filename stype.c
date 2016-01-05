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
        puts("open error.\n");
        return -1;
    }

    if ((bytes_read = getline(&buffer, &buffer_size, fp)) <= 0) {
        puts("parse error 0.\n");
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
    entry->total = strtof(buffer, NULL);
    if ((bytes_read = getline(&buffer, &buffer_size, fp)) <= 0) {
        puts("parse error 2.\n");
        free(buffer);
        fclose(fp);
        return -1;
    }
    entry->t = strtol(buffer, NULL, 10);
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
    left->total += right->total;
    // TODO
    left->t = left->t;

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

    if(fp == NULL) {
        return -1;
    }

    fprintf(fp, "%d\n", entry->size);
    fprintf(fp, "%f\n", entry->total);
    fprintf(fp, "%ld\n", entry->t);

    for (i = 0; i < size; ++i) {
        fprintf(fp, "%s,%f\n", entry->labels[i], entry->values[i]);
    }

    fclose(fp);

    return 0;
}


