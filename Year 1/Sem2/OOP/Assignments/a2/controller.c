/**
 * @file controller.c
 * @brief Implementation of the Controller module for managing materials.
 */

#include "controller.h"
#include "command.h"
#include "memento.h"
#include "add_material_command.h"
#include "delete_material_command.h"
#include "update_material_command.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Initializes the controller using the Command Pattern.
 * @param ctrl Pointer to the Controller structure.
 */
void init_controller_command(Controller *ctrl) {
    init_repository(&ctrl->repo);
    ctrl->undo_index = 0;
    ctrl->redo_index = 0;
    ctrl->memento_index = 0;
}

/**
 * @brief Initializes the controller using the Memento Pattern.
 * @param ctrl Pointer to the Controller structure.
 */
void init_controller_memento(Controller *ctrl) {
    init_repository(&ctrl->repo);
    ctrl->undo_index = 0;
    ctrl->redo_index = 0;
    ctrl->memento_index = 0;
    ctrl->memento_history[ctrl->memento_index++] = create_memento(&ctrl->repo);
}

/**
 * @brief Destroys the controller and frees allocated resources.
 * @param ctrl Pointer to the Controller structure.
 */
void destroy_controller(Controller *ctrl) {
    for (int i = 0; i < ctrl->undo_index; i++) {
        destroy_command(ctrl->undo_history[i]);
    }
    for (int i = 0; i < ctrl->redo_index; i++) {
        destroy_command(ctrl->redo_history[i]);
    }
    for (int i = 0; i < ctrl->memento_index; i++) {
        destroy_memento(ctrl->memento_history[i]);
    }
    destroy_repository(&ctrl->repo);
}

/**
 * @brief Adds a material to the repository.
 * @param ctrl Pointer to the Controller structure.
 * @param name Name of the material.
 * @param supplier Supplier of the material.
 * @param quantity Quantity of the material.
 * @param expiration_date Expiration date of the material.
 */
void add_material_ctrl(Controller *ctrl, const char *name, const char *supplier, int quantity, const char *expiration_date) {
    Command *cmd = create_add_material_command(&ctrl->repo, name, supplier, quantity, expiration_date);
    cmd->execute(cmd->data);
    ctrl->undo_history[ctrl->undo_index++] = cmd;
    ctrl->redo_index = 0;
}

/**
 * @brief Deletes a material from the repository.
 * @param ctrl Pointer to the Controller structure.
 * @param name Name of the material.
 * @param supplier Supplier of the material.
 * @param expiration_date Expiration date of the material.
 */
void delete_material_ctrl(Controller *ctrl, const char *name, const char *supplier, const char *expiration_date) {
    Command *cmd = create_delete_material_command(&ctrl->repo, name, supplier, expiration_date);
    cmd->execute(cmd->data);
    ctrl->undo_history[ctrl->undo_index++] = cmd;
    ctrl->redo_index = 0;
}

/**
 * @brief Lists expired materials in the repository.
 * @param ctrl Pointer to the Controller structure.
 * @param search_string Search string for filtering expired materials.
 */
void list_expired_materials_ctrl(Controller *ctrl, const char *search_string) {
    list_expired_materials(&ctrl->repo, search_string);
}

/**
 * @brief Lists materials by supplier in the repository.
 * @param ctrl Pointer to the Controller structure.
 * @param supplier Supplier of the materials.
 * @param max_quantity Maximum quantity of the materials.
 * @param ascending Sort order (1 for ascending, 0 for descending).
 */
void list_materials_by_supplier_ctrl(Controller *ctrl, const char *supplier, int max_quantity, int ascending) {
    if (ascending) {
        list_materials_by_supplier(&ctrl->repo, supplier, max_quantity);
    } else {
        list_materials_by_supplier_desc(&ctrl->repo, supplier, max_quantity);
    }
}

/**
 * @brief Updates the quantity of a material in the repository.
 * @param ctrl Pointer to the Controller structure.
 * @param name Name of the material.
 * @param supplier Supplier of the material.
 * @param expiration_date Expiration date of the material.
 * @param new_quantity New quantity of the material.
 */
void update_material_ctrl(Controller *ctrl, const char *name, const char *supplier, const char *expiration_date, int new_quantity) {
    Command *cmd = create_update_material_command(&ctrl->repo, name, supplier, expiration_date, new_quantity);
    cmd->execute(cmd->data);
    ctrl->undo_history[ctrl->undo_index++] = cmd;
    ctrl->redo_index = 0;
}

/**
 * @brief Performs an undo operation.
 * @param ctrl Pointer to the Controller structure.
 * @return 1 if undo was successful, 0 otherwise.
 */
int undo(Controller *ctrl) {
    if (ctrl->undo_index > 0) {
        Command *cmd = ctrl->undo_history[--ctrl->undo_index];
        cmd->undo(cmd->data);
        ctrl->redo_history[ctrl->redo_index++] = cmd;
        return 1;
    }
    return 0;
}

/**
 * @brief Performs a redo operation.
 * @param ctrl Pointer to the Controller structure.
 * @return 1 if redo was successful, 0 otherwise.
 */
int redo(Controller *ctrl) {
    if (ctrl->redo_index > 0) {
        Command *cmd = ctrl->redo_history[--ctrl->redo_index];
        cmd->execute(cmd->data);
        ctrl->undo_history[ctrl->undo_index++] = cmd;
        return 1;
    }
    return 0;
}