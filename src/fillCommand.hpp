#ifndef FILLCOMMAND_HPP
#define FILLCOMMAND_HPP

#include "command.hpp"

class FillCommand : public Command {
public:
    FillCommand(Application* app, Sketchpad * sketchpad);
    void undo() override;
    bool execute() override;
};

#endif
