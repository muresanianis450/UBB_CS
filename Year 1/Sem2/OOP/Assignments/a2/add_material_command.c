#include "add_material_command.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    Repository *repo;
    Material material;
} AddMaterialData;

void execute_add_material(void *data) {
    AddMaterialData *cmd_data = (AddMaterialData *)data;
    add_material(cmd_data->repo, cmd_data->material.name, cmd_data->material.supplier, cmd_data->material.quantity, cmd_data->material.expiration_date);
}

void undo_add_material(void *data) {
    AddMaterialData *cmd_data = (AddMaterialData *)data;
    delete_material(cmd_data->repo, cmd_data->material.name, cmd_data->material.supplier, cmd_data->material.expiration_date);
}

Command *create_add_material_command(Repository *repo, const char *name, const char *supplier, int quantity, const char *expiration_date) {
    Command *cmd = (Command *)malloc(sizeof(Command));
    AddMaterialData *data = (AddMaterialData *)malloc(sizeof(AddMaterialData));
    data->repo = repo;
    strncpy(data->material.name, name, NAME_LENGTH);
    strncpy(data->material.supplier, supplier, SUPPLIER_LENGTH);
    data->material.quantity = quantity;
    strncpy(data->material.expiration_date, expiration_date, DATE_LEN);
    cmd->execute = execute_add_material;
    cmd->undo = undo_add_material;
    cmd->data = data;
    return cmd;
}