#pragma once
#include "Action.h"
#include "Repository.h"
#include "Song.h"
#ifndef ACTIONUPDATE_H
#define ACTIONUPDATE_H
class UpdateAction : public Action {
private:
    Repository& repo;
    Song oldSong;
    Song newSong;

public:
    UpdateAction(Repository& repo, const Song& oldSong, const Song& newSong)
        : repo(repo), oldSong(oldSong), newSong(newSong) {}

    void executeUndo() override;

    void executeRedo() override;
};
#endif //ACTIONUPDATE_H
