#include "brushDownCommand.hpp"

BrushDownCommand::BrushDownCommand(Application* app, Sketchpad * sketchpad)
    : Command{app, sketchpad} {}

bool BrushDownCommand::execute() {
    sketchpad->setBrush(true);
    return true;
}
