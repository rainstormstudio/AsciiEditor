#include "drawCommand.hpp"

DrawCommand::DrawCommand(Application* app, Sketchpad * sketchpad)
    : Command{app, sketchpad} {}

bool DrawCommand::execute() {
    saveBackup();
    sketchpad->drawPoint();
    return true;
}
