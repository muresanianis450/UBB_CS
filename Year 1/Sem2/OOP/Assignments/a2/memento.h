// memento.h
#ifndef MEMENTO_H
#define MEMENTO_H

#include "repository.h"

typedef struct {
    Material *materials;
    int count;
    int capacity;
} Memento;

Memento *create_memento(Repository *repo);
void restore_memento(Repository *repo, Memento *memento);
void destroy_memento(Memento *memento);

#endif // MEMENTO_H