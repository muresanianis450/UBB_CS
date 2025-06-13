#ifndef DELETE_MATERIAL_COMMAND_H
#define DELETE_MATERIAL_COMMAND_H

#include "repository.h"
#include "command.h"

Command *create_delete_material_command(Repository *repo, const char *name, const char *supplier, const char *expiration_date);

#endif // DELETE_MATERIAL_COMMAND_H