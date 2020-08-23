#ifndef DRAWPOSCOMMAND_HPP
#define DRAWPOSCOMMAND_HPP

#include "command.hpp"

class Sketchpad;

class DrawPosCommand : public Command {
    Cpixel cpixel;
    int x, y;
public:
    DrawPosCommand(Application* app, Sketchpad * sketchpad, Cpixel cpixel, int x, int y);
    void saveBackup() override;
    void undo() override;
    bool execute() override;
};

#endif
