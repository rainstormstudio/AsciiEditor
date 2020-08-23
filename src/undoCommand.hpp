#ifndef UNDOCOMMAND_HPP
#define UNDOCOMMAND_HPP

#include "command.hpp"

class UndoCommand : public Command {
public:
    UndoCommand(Application* app, Sketchpad * sketchpad);
    void undo() override;
    bool execute() override;
};

#endif