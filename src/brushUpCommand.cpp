#include "brushUpCommand.hpp"

BrushUpCommand::BrushUpCommand(Application* app, Sketchpad * sketchpad)
    : Command{app, sketchpad} {}

bool BrushUpCommand::execute() {
    sketchpad->setBrush(false);
    return true;
}
