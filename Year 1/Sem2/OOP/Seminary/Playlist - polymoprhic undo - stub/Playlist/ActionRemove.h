#pragma once
#include "Action.h"
#include "Repository.h"
#include "Song.h"

#ifndef ACTIONREMOVE_H
#define ACTIONREMOVE_H
class RemoveAction : public Action {
private:
    Repository& repo;
    Song song;

public:
    RemoveAction(Repository& repo, const Song& song) : repo(repo), song(song) {}

    void executeUndo() override;


    void executeRedo() override;

};
#endif //ACTIONREMOVE_H
