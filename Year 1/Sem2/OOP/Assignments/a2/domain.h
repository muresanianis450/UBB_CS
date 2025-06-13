#ifndef DOMAIN_H
#define DOMAIN_H

#define NAME_LENGTH 50
#define SUPPLIER_LENGTH 50
#define DATE_LEN 11

typedef struct {
    char name[NAME_LENGTH];
    char supplier[SUPPLIER_LENGTH];
    int quantity;
    char expiration_date[DATE_LEN];
} Material;

Material *create_material(const char *name, const char *supplier, int quantity, const char *expiration_date);
int compare_dates(const char *date1, const char *date2);

#endif /* DOMAIN_H */
