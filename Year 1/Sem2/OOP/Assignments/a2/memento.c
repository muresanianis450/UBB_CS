/**
* @file memento.c
 * @brief Implementation of the Memento module for managing materials.
 */

#include "memento.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Creates a memento for the repository.
 * @param repo Pointer to the repository.
 * @return Pointer to the created memento.
 */
Memento *create_memento(Repository *repo) {
    Memento *memento = (Memento *)malloc(sizeof(Memento));
    memento->count = repo->count;
    memento->capacity = repo->capacity;
    memento->materials = (Material *)malloc(repo->capacity * sizeof(Material));
    memcpy(memento->materials, repo->materials, repo->count * sizeof(Material));
    return memento;
}

/**
 * @brief Restores the repository from a memento.
 * @param repo Pointer to the repository.
 * @param memento Pointer to the memento.
 */
void restore_memento(Repository *repo, Memento *memento) {
    repo->count = memento->count;
    repo->capacity = memento->capacity;
    repo->materials = (Material *)realloc(repo->materials, memento->capacity * sizeof(Material));
    memcpy(repo->materials, memento->materials, memento->count * sizeof(Material));
}

/**
 * @brief Destroys a memento and frees allocated resources.
 * @param memento Pointer to the memento.
 */
void destroy_memento(Memento *memento) {
    free(memento->materials);
    free(memento);
}