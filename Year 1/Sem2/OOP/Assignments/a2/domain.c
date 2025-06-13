#include "domain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Material *create_material(const char *name, const char *supplier, int quantity, const char *expiration_date) {
    Material *m = (Material *)malloc(sizeof(Material));
    if (m != NULL) {
        strcpy(m->name, name);
        strcpy(m->supplier, supplier);
        m->quantity = quantity;
        strcpy(m->expiration_date, expiration_date);
    }
    return m;
}

int compare_dates(const char *date1, const char *date2) {
    return strcmp(date1, date2) < 0;
}
