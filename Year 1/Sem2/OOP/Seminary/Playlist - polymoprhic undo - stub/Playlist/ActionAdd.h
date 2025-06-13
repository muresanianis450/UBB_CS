#pragma once
#include "Action.h"
#include "Repository.h"
#include "Song.h"
#ifndef ACTIONADD_H
#define ACTIONADD_H

class AddAction : public Action {
private:
  Repository& repo;
  Song song;

public:
  AddAction(Repository& repo, const Song& song) : repo(repo), song(song) {}

  void executeUndo() override ;

  void executeRedo() override;

};

#endif //ACTIONADD_H
