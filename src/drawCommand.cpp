#include "drawCommand.hpp"

DrawCommand::DrawCommand(Application* app, Sketchpad * sketchpad)
    : Command{app, sketchpad} {}

void DrawCommand::undo() {
    sketchpad->drawPoint(backupInfo, backupX, backupY);
}

bool DrawCommand::execute() {
    saveBackup();
    sketchpad->drawPoint();
    return true;
}
