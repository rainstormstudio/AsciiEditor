#ifndef SAVEFILECOMMAND_HPP
#define SAVEFILECOMMAND_HPP

#include "command.hpp"

class SaveFileCommand : public Command {
public:
    SaveFileCommand(Application* app, Sketchpad * sketchpad);
    void undo() override;
    bool execute() override;
};

#endif
