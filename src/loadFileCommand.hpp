#ifndef LOADFILECOMMAND_HPP
#define LOADFILECOMMAND_HPP

#include "command.hpp"

class LoadFileCommand : public Command {
public:
    LoadFileCommand(Application* app, Sketchpad * sketchpad);
    void undo() override;
    bool execute() override;
};

#endif
