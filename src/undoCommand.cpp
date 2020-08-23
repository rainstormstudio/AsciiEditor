#include "undoCommand.hpp"

UndoCommand::UndoCommand(Application* app, Sketchpad * sketchpad)
    : Command(app, sketchpad) {}

void UndoCommand::undo() {}

bool UndoCommand::execute() {
    app->undo();
    return false;
}
