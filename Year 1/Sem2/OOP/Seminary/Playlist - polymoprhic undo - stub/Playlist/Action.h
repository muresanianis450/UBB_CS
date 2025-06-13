#pragma once

#ifndef ACTION_H
#define ACTION_H

class Action {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
    virtual ~Action() = default;
};

#endif //ACTION_H
