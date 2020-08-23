#ifndef DRAWCOMMAND_HPP
#define DRAWCOMMAND_HPP

#include "command.hpp"

class DrawCommand : public Command {
public:
    DrawCommand(Application* app, Sketchpad * sketchpad);
    bool execute() override;
};

#endif
