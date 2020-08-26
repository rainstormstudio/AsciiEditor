#include "loadFileCommand.hpp"
#include "textInputpad.hpp"
#include "quitException.hpp"

LoadFileCommand::LoadFileCommand(Application* app, Sketchpad * sketchpad)
    : Command{app, sketchpad} {}

void LoadFileCommand::undo() {}

bool LoadFileCommand::execute() {
    TextInputpad * textInputpad = nullptr;
    try {
        textInputpad = new TextInputpad(app, (app->getGFX()->getScreenRows() - 6) / 2, (app->getGFX()->getScreenCols() - 20) / 2, 20, 6, "LOAD FILE");
    } catch (QuitException) {
        delete textInputpad;
        throw;
        return false;
    }
    sketchpad->loadFromFile(textInputpad->getText());
    delete textInputpad;
    return false;
}
