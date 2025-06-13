//
// Created by mures on 4/28/2025.
//

#include "ActionRemove.h"

void RemoveAction::executeUndo() {
    repo.addSong(song);
}
void RemoveAction::executeRedo() {
    repo.removeSong(song);
}