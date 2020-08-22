#include "statuspad.hpp"

Statuspad::Statuspad(Graphics* gfx, SDL_Event* event, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Sketchpad* sketchpad)
    : Panel(gfx, event, top, left, width, height), sketchpad{sketchpad} {
}

void Statuspad::update() {
}

void Statuspad::render() {
    drawBorder("STATUS");
    int x = sketchpad->getCursorX();
    int y = sketchpad->getCursorY();
    if (x != -1 && y != -1) {
        gfx->write("x: " + std::to_string(x), left + 1, top + 1);
        gfx->write("y: " + std::to_string(y), left + 1, top + 2);
    } else {
        gfx->write("x: -", left + 1, top + 1);
        gfx->write("y: -", left + 1, top + 2);
    }
    fillBackColor(40, 90, 80, 255);
    fillForeColor(0, 255, 255, 255);
}
