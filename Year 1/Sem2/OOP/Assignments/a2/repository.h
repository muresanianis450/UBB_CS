#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "domain.h"

typedef struct {
    Material *materials;
    int count;
    int capacity;
} Repository;

void init_repository(Repository *repo);
void destroy_repository(Repository *repo);
int find_material(Repository *repo, const char *name, const char *supplier, const char *expiration_date);
void add_material(Repository *repo, const char *name, const char *supplier, int quantity, const char *expiration_date);
void delete_material(Repository *repo, const char *name, const char *supplier, const char *expiration_date);
void list_expired_materials(Repository *repo, const char *search_string);
void list_materials_by_supplier(Repository *repo, const char *supplier, int max_quantity);
void list_materials_by_supplier_desc(Repository *repo, const char *supplier, int max_quantity);
void resize_repository(Repository *repo);

#endif // REPOSITORY_H