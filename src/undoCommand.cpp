#include "undoCommand.hpp"

UndoCommand::UndoCommand(Application* app, Sketchpad * sketchpad)
    : Command(app, sketchpad) {}

bool UndoCommand::execute() {
    app->undo();
    return false;
}
