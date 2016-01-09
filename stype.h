#ifndef SHIEH_TYPE
#define SHIEH_TYPE


#include <math.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>


typedef struct {
    int size;
    double total;
    time_t t;
    char **labels;
    double *values;
} ledger_entry;


int parse_line(char *line, char **label, double *value);

int parse_entry(char* fn, ledger_entry *entry);

int merge_entry(ledger_entry *left, ledger_entry *right);

int add_entry(ledger_entry *le, char *label, double value);

int index_of_e(ledger_entry *le, char *label);

int check_date(char *fn, char *backup);

int save_entry(char* fn, ledger_entry *entry);

void prepare_entry(int flag, ledger_entry *entry, int dayofyear);


#endif /* ifndef SHIEH_TYPE */
