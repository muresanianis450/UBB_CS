//
// Created by mures on 4/28/2025.
//

#include "ActionAdd.h"


void AddAction::executeUndo() {
    repo.removeSong(song);
}
void AddAction::executeRedo() {
    repo.addSong(song);
}