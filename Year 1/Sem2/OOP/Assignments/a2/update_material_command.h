#ifndef UPDATE_MATERIAL_COMMAND_H
#define UPDATE_MATERIAL_COMMAND_H

#include "command.h"
#include "repository.h"

Command *create_update_material_command(Repository *repo, const char *name, const char *supplier, const char *expiration_date, int new_quantity);

#endif // UPDATE_MATERIAL_COMMAND_H