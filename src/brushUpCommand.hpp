#ifndef BRUSHUPCOMMAND_HPP
#define BRUSHUPCOMMAND_HPP

#include "command.hpp"

class BrushUpCommand : public Command {
public:
    BrushUpCommand(Application* app, Sketchpad * sketchpad);
    void undo() override;
    bool execute() override;
};

#endif
