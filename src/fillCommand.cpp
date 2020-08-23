#include "fillCommand.hpp"

FillCommand::FillCommand(Application* app, Sketchpad * sketchpad)
    : Command{app, sketchpad} {}

void FillCommand::undo() {
}

bool FillCommand::execute() {
    sketchpad->fillArea();
    return false;
}
