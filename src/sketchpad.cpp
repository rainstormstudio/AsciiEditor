#include "sketchpad.hpp"

Sketchpad::Sketchpad(Graphics* gfx, SDL_Event* event, unsigned int top, unsigned int left, unsigned int width, unsigned int height)
    : Panel(gfx, event, top, left, width, height) {
    cpixels = std::vector<std::vector<Cpixel>>(height);
    for (unsigned int i = 0; i < height; ++i) {
        cpixels[i] = std::vector<Cpixel>(width);
        for (unsigned int j = 0; j < width; ++j) {
            cpixels[i][j] = {'0', 0, 0, 0, 0, 100, 100, 100, 255};
        }
    }
    cursorX = 0;
    cursorY = 0;
}

void Sketchpad::drawPoint(Uint8 ch, int x, int y, Uint8 r , Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    cpixels[y][x] = {ch, r, g, b, a, br, bg, bb, ba};
}

void Sketchpad::update() {
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

void Sketchpad::render() {
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            //std::cout << cpixels[i][j].ch << " (" << i << "," << j << ")" << std::endl;
            gfx->setCh(cpixels[i][j].ch, j + left, i + top);
            gfx->setForeColor(cpixels[i][j].r, cpixels[i][j].g, cpixels[i][j].b, cpixels[i][j].a, j + left, i + top);
            gfx->setBackColor(cpixels[i][j].br, cpixels[i][j].bg, cpixels[i][j].bb, cpixels[i][j].ba, j + left, i + top);
        }
    }
    if (cursorX != -1 && cursorY != -1) {
        gfx->setBackColor(255, 0, 0, 255, cursorX + left, cursorY + top);
    }
}

int Sketchpad::getCursorX() const { return cursorX; }

int Sketchpad::getCursorY() const { return cursorY; }
