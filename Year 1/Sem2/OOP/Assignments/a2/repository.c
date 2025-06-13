#include "repository.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void init_repository(Repository *repo) {
    repo->count = 0;
    repo->capacity = 10; // Initial capacity
    repo->materials = (Material *)malloc(repo->capacity * sizeof(Material));

    // Add initial items
    add_material(repo, "Butter", "Supplier4", 150, "3000-03-15");
    add_material(repo, "Yeast", "Supplier5", 50, "3000-11-30");
    add_material(repo, "Milk", "Supplier6", 120, "3000-10-25");
    add_material(repo, "Eggs", "Supplier7", 180, "2021-09-20");
    add_material(repo, "Baking Powder", "Supplier8", 75, "2024-05-10");
    add_material(repo, "Vanilla", "Supplier9", 60, "2023-07-22");
    add_material(repo, "Chocolate", "Supplier10", 90, "2022-08-15");
    add_material(repo, "Flour", "Supplier1", 100, "2021-12-31");
    add_material(repo, "Sugar", "Supplier2", 200, "2022-01-31");
    add_material(repo, "Salt", "Supplier3", 300, "2022-02-28");
}

void resize_repository(Repository *repo) {
    repo->capacity *= 2;
    repo->materials = (Material *)realloc(repo->materials, repo->capacity * sizeof(Material));
}

void add_material(Repository *repo, const char *name, const char *supplier, int quantity, const char *expiration_date) {
    int index = find_material(repo, name, supplier, expiration_date);
    if (index != -1) {
        repo->materials[index].quantity += quantity;
    } else {
        if (repo->count == repo->capacity) {
            resize_repository(repo);
        }
        Material new_material;
        strcpy(new_material.name, name);
        strcpy(new_material.supplier, supplier);
        new_material.quantity = quantity;
        strcpy(new_material.expiration_date, expiration_date);
        repo->materials[repo->count++] = new_material;
    }
}

void delete_material(Repository *repo, const char *name, const char *supplier, const char *expiration_date) {
    int index = find_material(repo, name, supplier, expiration_date);
    if (index != -1) {
        for (int i = index; i < repo->count - 1; i++) {
            repo->materials[i] = repo->materials[i + 1];
        }
        repo->count--;
    }
}

void list_expired_materials(Repository *repo, const char *search_string) {
    for (int i = 0; i < repo->count; i++) {
        if (strstr(repo->materials[i].name, search_string) != NULL) {
            printf("Name: %s, Supplier: %s, Quantity: %d, Expiration Date: %s\n",
                   repo->materials[i].name, repo->materials[i].supplier, repo->materials[i].quantity, repo->materials[i].expiration_date);
        }
    }
}

void list_materials_by_supplier(Repository *repo, const char *supplier, int max_quantity) {
    for (int i = 0; i < repo->count; i++) {
        if (strcmp(repo->materials[i].supplier, supplier) == 0 && repo->materials[i].quantity < max_quantity) {
            printf("Name: %s, Supplier: %s, Quantity: %d, Expiration Date: %s\n",
                   repo->materials[i].name, repo->materials[i].supplier, repo->materials[i].quantity, repo->materials[i].expiration_date);
        }
    }
}
int find_material(Repository *repo, const char *name, const char *supplier, const char *expiration_date) {
    for (int i = 0; i < repo->count; i++) {
        if (strcmp(repo->materials[i].name, name) == 0 &&
            strcmp(repo->materials[i].supplier, supplier) == 0 &&
            strcmp(repo->materials[i].expiration_date, expiration_date) == 0) {
            return i;
            }
    }
    return -1;
}

void list_materials_by_supplier_desc(Repository *repo, const char *supplier, int max_quantity) {
    Material *filtered = (Material *)malloc(repo->count * sizeof(Material));
    int filtered_count = 0;

    for (int i = 0; i < repo->count; i++) {
        if (strcmp(repo->materials[i].supplier, supplier) == 0 && repo->materials[i].quantity < max_quantity) {
            filtered[filtered_count++] = repo->materials[i];
        }
    }

    for (int i = 0; i < filtered_count - 1; i++) {
        for (int j = i + 1; j < filtered_count; j++) {
            if (filtered[i].quantity < filtered[j].quantity) {
                Material temp = filtered[i];
                filtered[i] = filtered[j];
                filtered[j] = temp;
            }
        }
    }

    for (int i = 0; i < filtered_count; i++) {
        printf("Name: %s, Supplier: %s, Quantity: %d, Expiration Date: %s\n",
               filtered[i].name, filtered[i].supplier, filtered[i].quantity, filtered[i].expiration_date);
    }

    free(filtered);
}
void destroy_repository(Repository *repo) {
    free(repo->materials);
}