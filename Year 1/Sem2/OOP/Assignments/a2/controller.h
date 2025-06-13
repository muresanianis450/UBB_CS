#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "repository.h"
#include "command.h"
#include "memento.h"

#define MAX_HISTORY 100

typedef struct {
   Repository repo;
   Command *undo_history[MAX_HISTORY];
   Command *redo_history[MAX_HISTORY];
   Memento *memento_history[MAX_HISTORY];
   int undo_index;
   int redo_index;
   int memento_index;
} Controller;

void init_controller_command(Controller *ctrl);
void init_controller_memento(Controller *ctrl);
void destroy_controller(Controller *ctrl);

void add_material_ctrl(Controller *ctrl, const char *name, const char *supplier, int quantity, const char *expiration_date);
void delete_material_ctrl(Controller *ctrl, const char *name, const char *supplier, const char *expiration_date);
void list_expired_materials_ctrl(Controller *ctrl, const char *search_string);
void list_materials_by_supplier_ctrl(Controller *ctrl, const char *supplier, int max_quantity, int ascending);
void update_material_ctrl(Controller *ctrl, const char *name, const char *supplier, const char *expiration_date, int new_quantity);

int undo(Controller *ctrl);
int redo(Controller *ctrl);

#endif // CONTROLLER_H