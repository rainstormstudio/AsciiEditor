#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "application.hpp"
#include "sketchpad.hpp"
#include "charpad.hpp"
#include "palettepad.hpp"

class Command {
protected:
    Application* app;
    Sketchpad* sketchpad;
    int backupX;
    int backupY;
    Cpixel backupInfo;
public:
    Command(Application* app, Sketchpad* sketchpad);
    virtual void saveBackup();
    virtual void undo() = 0;
    virtual bool execute() = 0;
};

#endif
