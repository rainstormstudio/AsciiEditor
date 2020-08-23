#include "filepad.hpp"
#include "button.hpp"

Filepad::Filepad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height)
    : Panel(app, top, left, width, height) {
    newButton = new Button(app, top + 1, left + 1, 6, 1, "NEW");
    saveButton = new Button(app, top + 2, left + 1, 6, 1, "SAVE");
    loadButton = new Button(app, top + 3, left + 1, 6, 1, "LOAD");
}

Filepad::~Filepad() {
    delete newButton;
    delete saveButton;
    delete loadButton;
}

bool Filepad::newClicked() const {
    return newButton->hasPressed();
}

bool Filepad::saveClicked() const {
    return saveButton->hasPressed();
}

bool Filepad::loadClicked() const {
    return loadButton->hasPressed();
}

void Filepad::update() {
    newButton->update();
    saveButton->update();
    loadButton->update();
}

void Filepad::render() {
    drawBorder("FILE");
    fillBackColor(40, 90, 80, 255);
    fillForeColor(0, 255, 255, 255);
    newButton->render();
    saveButton->render();
    loadButton->render();
}
