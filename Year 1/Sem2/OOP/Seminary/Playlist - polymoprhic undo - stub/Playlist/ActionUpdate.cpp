//
// Created by mures on 4/28/2025.
//

#include "ActionUpdate.h"

void UpdateAction::executeUndo() {
    repo.updateSong(oldSong);
}
void UpdateAction::executeRedo() {
    repo.updateSong(newSong);
}