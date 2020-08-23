#ifndef BRUSHDOWNCOMMAND_HPP
#define BRUSHDOWNCOMMAND_HPP

#include "command.hpp"

class BrushDownCommand : public Command {
public:
    BrushDownCommand(Application* app, Sketchpad * sketchpad);
    void undo() override;
    bool execute() override;
};

#endif
