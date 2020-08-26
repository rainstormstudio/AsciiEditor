#ifndef NEWFILECOMMAND_HPP
#define NEWFILECOMMAND_HPP

#include "command.hpp"

class NewFileCommand : public Command {
public:
    NewFileCommand(Application* app, Sketchpad * sketchpad);
    void undo() override;
    bool execute() override;
};

#endif
