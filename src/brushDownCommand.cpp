#include "brushDownCommand.hpp"

BrushDownCommand::BrushDownCommand(Application* app, Sketchpad * sketchpad)
    : Command{app, sketchpad} {}

void BrushDownCommand::undo() {}

bool BrushDownCommand::execute() {
    sketchpad->setBrush(true);
    return true;
}
