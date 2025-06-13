#ifndef COMMAND_H
#define COMMAND_H

typedef struct {
    void (*execute)(void *);
    void (*undo)(void *);
    void *data;
} Command;

Command *create_command(void (*execute)(void *), void (*undo)(void *), void *data);
void destroy_command(Command *cmd);

#endif // COMMAND_H