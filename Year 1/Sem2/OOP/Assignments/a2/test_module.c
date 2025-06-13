/**
 * @file test_module.c
 * @brief Implementation of test functions for the repository module.
 */

#include "repository.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Tests the add_material function.
 */
void test_add_material() {
    Repository repo;
    init_repository(&repo);

    add_material(&repo, "TestMaterial1", "TestSupplier1", 10, "2023-12-01");
    assert(repo.count == 11); // 10 initial items + 1 added
    assert(strcmp(repo.materials[10].name, "TestMaterial1") == 0);

    destroy_repository(&repo);
    printf("Add material test passed.\n");
}

/**
 * @brief Tests the find_material function.
 */
void test_find_material() {
    Repository repo;
    init_repository(&repo);

    int index = find_material(&repo, "Butter", "Supplier4", "3000-03-15");
    assert(index != -1);

    index = find_material(&repo, "NonExistent", "Supplier", "2023-12-01");
    assert(index == -1);

    destroy_repository(&repo);
    printf("Find material test passed.\n");
}

/**
 * @brief Tests the delete_material function.
 */
void test_delete_material() {
    Repository repo;
    init_repository(&repo);

    delete_material(&repo, "Butter", "Supplier4", "3000-03-15");
    assert(repo.count == 9);

    int index = find_material(&repo, "Butter", "Supplier4", "3000-03-15");
    assert(index == -1);

    destroy_repository(&repo);
    printf("Delete material test passed.\n");
}

/**
 * @brief Tests the list_expired_materials function.
 */
void test_list_expired_materials() {
    Repository repo;
    init_repository(&repo);

    printf("Expired materials:\n");
    list_expired_materials(&repo, "2021");

    destroy_repository(&repo);
    printf("List expired materials test passed.\n");
}

/**
 * @brief Tests the list_materials_by_supplier function.
 */
void test_list_materials_by_supplier() {
    Repository repo;
    init_repository(&repo);

    printf("Materials by Supplier1 with max quantity 150:\n");
    list_materials_by_supplier(&repo, "Supplier1", 150);

    destroy_repository(&repo);
    printf("List materials by supplier test passed.\n");
}

/**
 * @brief Runs all the test functions.
 */
void run_tests() {
    test_add_material();
    test_find_material();
    test_delete_material();
    test_list_expired_materials();
    test_list_materials_by_supplier();
}