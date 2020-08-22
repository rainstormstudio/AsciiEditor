#include "charpad.hpp"

Charpad::Charpad(Graphics* gfx, SDL_Event* event, unsigned int top, unsigned int left, unsigned int width, unsigned int height)
    : Panel(gfx, event, top, left, width, height) {
    selected = 0;
    cursorX = 0;
    cursorY = 0;
}

void Charpad::update() {
    int x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    x = gfx->getPosCol(x);
    y = gfx->getPosRow(y);
    if (x - left >= 0 && x - left < width && y - top >= 0 && y - top < height) {
        cursorX = x - left;
        cursorY = y - top;
    } else {
        cursorX = -1;
        cursorY = -1;
    }
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (cursorX - 2 >= 0 && cursorX - 2 < 16
            && cursorY - 2 >= 0 && cursorY - 2 < 16) {
            selected = (cursorY - 2) * 16 + (cursorX - 2);
        }
    }
}

void Charpad::render() {
    drawBorder("CHAR");
    fillBackColor(40, 90, 80, 255);
    fillForeColor(0, 255, 255, 255);
    int x = 0, y = 0;
    for (unsigned int i = 0; i < 16 * 16; ++i) {
        if (i > 0 && i % 16 == 0) {
            x = 0;
            ++y;
        }
        gfx->setCh(i, x + left + 2, y + top + 2);
        ++x;            
    }
    int selectedX = selected % 16;
    int selectedY = selected / 16;
    for (unsigned int i = 0; i < 18; ++i) {
        gfx->setBackColor(255, 190, 0, 255, i + left + 1, top + 2 + selectedY);
    }
    for (unsigned int i = 0; i < 18; ++i) {
        gfx->setBackColor(255, 190, 0, 255, left + 2 + selectedX, i + top + 1);
        if (i + 1 == selectedY + 2) {
            gfx->setForeColor(0, 120, 255, 255, left + 2 + selectedX, i + top + 1);
        }
    }
    if (cursorX >= 2 && cursorX < 18 && cursorY >= 2 && cursorY < 18) {
        for (unsigned int i = 0; i < 18; ++i) {
            gfx->setForeColor(120, 90, 10, 255, i + left + 1, top + cursorY);
        }
        for (unsigned int i = 0; i < 18; ++i) {
            gfx->setForeColor(120, 90, 10, 255, left + cursorX, i + top + 1);
            if (i + 1 == cursorY) {
                gfx->setForeColor(80, 255, 0, 255, left + cursorX, i + top + 1);
            }
        }
    }
}

Uint8 Charpad::getSelected() const { return selected; }
