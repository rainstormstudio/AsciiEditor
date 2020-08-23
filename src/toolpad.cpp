#include "toolpad.hpp"

Toolpad::Toolpad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height)
    : Panel(app, top, left, width, height) {
    selected = 0;
}

void Toolpad::update() {
    updateCursor();
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (cursorX - 1 >= 0 && cursorX - 1 < width
            && cursorY - 1 >= 0 && cursorY - 1 < 3) {
            selected = cursorY - 1;
        }
    }
}

void Toolpad::render() {
    drawBorder("TOOLS");
    fillBackColor(40, 90, 80, 255);
    fillForeColor(0, 255, 255, 255);
    gfx->write(">", left + 1, top + 1 + selected);
    gfx->write("draw", left + 2, top + 1);
    gfx->write("erase", left + 2, top + 2);
    gfx->write("fill", left + 2, top + 3);
    for (unsigned int i = 1; i < width - 1; ++i) {
        gfx->setBackColor(255, 190, 0, 255, left + i, top + 1 + selected);
        gfx->setForeColor(0, 120, 255, 255, left + i, top + 1 + selected);
    }
    if (cursorX - 1 >= 0 && cursorX - 1 < width
        && cursorY - 1 >= 0 && cursorY - 1 < 3) {
        for (unsigned int i = 1; i < width - 1; ++i) {
            gfx->setForeColor(80, 255, 0, 255, left + i, top + cursorY);
        }
    }
}

unsigned int Toolpad::getSelected() const {
    return selected;
}
