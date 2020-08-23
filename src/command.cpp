#include "command.hpp"

Command::Command(Application* app, Sketchpad* sketchpad)
    : app{app}, sketchpad{sketchpad} {
    backupX = -1;
    backupY = -1;
}

void Command::saveBackup() {
    backupX = sketchpad->getCursorX();
    backupY = sketchpad->getCursorY();
    backupInfo = sketchpad->getCellInfo(backupX, backupY);
}

void Command::undo() {
    sketchpad->drawPoint(backupInfo, backupX, backupY);
}
