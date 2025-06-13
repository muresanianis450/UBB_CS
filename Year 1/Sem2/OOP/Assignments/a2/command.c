/**
* @file command.c
 * @brief Implementation of the Command module for managing materials.
 */

#include "command.h"
#include <stdlib.h>

/**
 * @brief Creates a command.
 * @param execute Function pointer to the execute function.
 * @param undo Function pointer to the undo function.
 * @param data Pointer to the command data.
 * @return Pointer to the created command.
 */
Command *create_command(void (*execute)(void *), void (*undo)(void *), void *data) {
    Command *cmd = (Command *)malloc(sizeof(Command));
    cmd->execute = execute;
    cmd->undo = undo;
    cmd->data = data;
    return cmd;
}

/**
 * @brief Destroys a command and frees allocated resources.
 * @param cmd Pointer to the command.
 */
void destroy_command(Command *cmd) {
    free(cmd->data);
    free(cmd);
}