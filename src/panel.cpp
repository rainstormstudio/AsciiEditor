#include "panel.hpp"

Panel::Panel(Graphics* gfx, unsigned int top, unsigned int left, unsigned int width, unsigned int height)
    : gfx{gfx}, top{top}, left{left}, width{width}, height{height} {}

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
        gfx->write("[" + title + "]", left + 2, top);
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
