#include "saveFileCommand.hpp"
#include "textInputpad.hpp"
#include "quitException.hpp"

SaveFileCommand::SaveFileCommand(Application* app, Sketchpad * sketchpad)
    : Command(app, sketchpad) {}

void SaveFileCommand::undo() {}

bool SaveFileCommand::execute() {
    TextInputpad* textInputpad = nullptr;
    try {
        textInputpad = new TextInputpad(app, (app->getGFX()->getScreenRows() - 6) / 2, (app->getGFX()->getScreenCols() - 20) / 2, 20, 6, "SAVE FILE");
    } catch (QuitException) {
        delete textInputpad;
        throw;
        return false;
    }
    sketchpad->saveToFile(textInputpad->getText());
    delete textInputpad;
    return false;
}
