#include "drawPosCommand.hpp"
#include "sketchpad.hpp"

DrawPosCommand::DrawPosCommand(Application* app, Sketchpad * sketchpad, Cpixel cpixel, int x, int y)
    : Command{app, sketchpad}, cpixel{cpixel}, x{x}, y{y}  {}

void DrawPosCommand::saveBackup() {
    backupX = x;
    backupY = y;
    backupInfo = sketchpad->getCellInfo(x, y);
}

void DrawPosCommand::undo() {
    sketchpad->drawPoint(backupInfo, backupX, backupY);
}

bool DrawPosCommand::execute() {
    saveBackup();
    sketchpad->drawPoint(cpixel, x, y);
    return true;
}