#include "brushUpCommand.hpp"

BrushUpCommand::BrushUpCommand(Application* app, Sketchpad * sketchpad)
    : Command{app, sketchpad} {}

void BrushUpCommand::undo() {}

bool BrushUpCommand::execute() {
    sketchpad->setBrush(false);
    return true;
}
