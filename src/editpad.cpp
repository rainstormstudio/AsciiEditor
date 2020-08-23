#include "editpad.hpp"
#include "button.hpp"
#include "application.hpp"

Editpad::Editpad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height) 
    : Panel(app, top, left, width, height) {
    undoButton = new Button(app, top + 1, left + 1, 6, 1, "UNDO");
}
Editpad::~Editpad() {
    delete undoButton;
}

bool Editpad::undo() const {
    return undoButton->hasPressed();
}

void Editpad::update() {
    undoButton->update();
}

void Editpad::render() {
    drawBorder("EDIT");
    fillBackColor(40, 90, 80, 255);
    fillForeColor(0, 255, 255, 255);
    undoButton->render();
}
