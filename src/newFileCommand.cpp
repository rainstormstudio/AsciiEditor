#include "newFileCommand.hpp"

NewFileCommand::NewFileCommand(Application* app, Sketchpad * sketchpad)
    : Command{app, sketchpad} {}

void NewFileCommand::undo() {}

bool NewFileCommand::execute() {
    sketchpad->clear();
    return false;
}
