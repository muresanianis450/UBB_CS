#include "update_material_command.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    Repository *repo;
    char name[NAME_LENGTH];
    char supplier[SUPPLIER_LENGTH];
    char expiration_date[DATE_LEN];
    int old_quantity;
    int new_quantity;
} UpdateMaterialData;

void execute_update_material(void *data) {
    UpdateMaterialData *cmd_data = (UpdateMaterialData *)data;
    for (int i = 0; i < cmd_data->repo->count; i++) {
        Material *material = &cmd_data->repo->materials[i];
        if (strcmp(material->name, cmd_data->name) == 0 &&
            strcmp(material->supplier, cmd_data->supplier) == 0 &&
            strcmp(material->expiration_date, cmd_data->expiration_date) == 0) {
            cmd_data->old_quantity = material->quantity;
            material->quantity = cmd_data->new_quantity;
            return;
        }
    }
}

void undo_update_material(void *data) {
    UpdateMaterialData *cmd_data = (UpdateMaterialData *)data;
    for (int i = 0; i < cmd_data->repo->count; i++) {
        Material *material = &cmd_data->repo->materials[i];
        if (strcmp(material->name, cmd_data->name) == 0 &&
            strcmp(material->supplier, cmd_data->supplier) == 0 &&
            strcmp(material->expiration_date, cmd_data->expiration_date) == 0) {
            material->quantity = cmd_data->old_quantity;
            return;
        }
    }
}

Command *create_update_material_command(Repository *repo, const char *name, const char *supplier, const char *expiration_date, int new_quantity) {
    Command *cmd = (Command *)malloc(sizeof(Command));
    UpdateMaterialData *data = (UpdateMaterialData *)malloc(sizeof(UpdateMaterialData));
    data->repo = repo;
    strncpy(data->name, name, NAME_LENGTH);
    strncpy(data->supplier, supplier, SUPPLIER_LENGTH);
    strncpy(data->expiration_date, expiration_date, DATE_LEN);
    data->new_quantity = new_quantity;
    cmd->execute = execute_update_material;
    cmd->undo = undo_update_material;
    cmd->data = data;
    return cmd;
}