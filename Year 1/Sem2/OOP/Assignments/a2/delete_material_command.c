#include "delete_material_command.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    Repository *repo;
    char name[NAME_LENGTH];
    char supplier[SUPPLIER_LENGTH];
    char expiration_date[DATE_LEN];
    Material deleted_material;
} DeleteMaterialData;

void execute_delete_material(void *data) {
    DeleteMaterialData *cmd_data = (DeleteMaterialData *)data;
    for (int i = 0; i < cmd_data->repo->count; i++) {
        Material *material = &cmd_data->repo->materials[i];
        if (strcmp(material->name, cmd_data->name) == 0 &&
            strcmp(material->supplier, cmd_data->supplier) == 0 &&
            strcmp(material->expiration_date, cmd_data->expiration_date) == 0) {
            cmd_data->deleted_material = *material;
            delete_material(cmd_data->repo, cmd_data->name, cmd_data->supplier, cmd_data->expiration_date);
            return;
            }
    }
}

void undo_delete_material(void *data) {
    DeleteMaterialData *cmd_data = (DeleteMaterialData *)data;
    add_material(cmd_data->repo, cmd_data->deleted_material.name, cmd_data->deleted_material.supplier, cmd_data->deleted_material.quantity, cmd_data->deleted_material.expiration_date);
}

Command *create_delete_material_command(Repository *repo, const char *name, const char *supplier, const char *expiration_date) {
    Command *cmd = (Command *)malloc(sizeof(Command));
    DeleteMaterialData *data = (DeleteMaterialData *)malloc(sizeof(DeleteMaterialData));
    data->repo = repo;
    strncpy(data->name, name, NAME_LENGTH);
    strncpy(data->supplier, supplier, SUPPLIER_LENGTH);
    strncpy(data->expiration_date, expiration_date, DATE_LEN);
    cmd->execute = execute_delete_material;
    cmd->undo = undo_delete_material;
    cmd->data = data;
    return cmd;
}