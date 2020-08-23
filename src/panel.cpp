#include "panel.hpp"
#include "application.hpp"

Panel::Panel(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height)
    : app{app}, top{top}, left{left}, width{width}, height{height} {
    gfx = app->getGFX();
    event = app->getEvent();
    cursorX = -1;
    cursorY = -1;
}

void Panel::drawBorder(std::string title) {
    for (unsigned int i = 1; i < height - 1; ++i) {
        gfx->setCh(186, left, top + i);
        gfx->setCh(186, left + width - 1, top + i);
    }
    for (unsigned int i = 1; i < width - 1; ++i) {
        gfx->setCh(205, left + i, top);
        gfx->setCh(205, left + i, top + height - 1);
    }
    gfx->setCh(201, left, top);
    gfx->setCh(187, left + width - 1, top);
    gfx->setCh(200, left, top + height - 1);
    gfx->setCh(188, left + width - 1, top + height - 1);
    if (title != "" && title.length() < width - 6) {
        gfx->write("[" + title + "]", left + 1, top);
    }
}

void Panel::fillBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            gfx->setBackColor(r, g, b, a, j + left, i + top);
        }
    }
}

void Panel::fillForeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            gfx->setForeColor(r, g, b, a, j + left, i + top);
        }
    }
}

bool Panel::validPos() const {
    if (cursorX != -1 && cursorY != -1) {
        return true;
    } else {
        return false;
    }
}

unsigned int Panel::getTop() const { return top; }

unsigned int Panel::getLeft() const { return left; }

void Panel::updateCursor() {
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
}
