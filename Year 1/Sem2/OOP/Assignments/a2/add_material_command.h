#ifndef ADD_MATERIAL_COMMAND_H
#define ADD_MATERIAL_COMMAND_H

#include "repository.h"
#include "command.h"

Command *create_add_material_command(Repository *repo, const char *name, const char *supplier, int quantity, const char *expiration_date);

#endif // ADD_MATERIAL_COMMAND_H