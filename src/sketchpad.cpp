#include "sketchpad.hpp"

Sketchpad::Sketchpad(Graphics* gfx, SDL_Event* event, unsigned int top, unsigned int left, unsigned int width, unsigned int height)
    : Panel(gfx, event, top, left, width, height) {
    cpixels = std::vector<std::vector<Cpixel>>(height);
    for (unsigned int i = 0; i < height; ++i) {
        cpixels[i] = std::vector<Cpixel>(width);
        for (unsigned int j = 0; j < width; ++j) {
            cpixels[i][j] = {0, 0, 0, 0, 0, 100, 100, 100, 255};
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
        unsigned int x = cursorX + left;
        unsigned int y = cursorY + top;
        int r = (cpixels[cursorY][cursorX].r + 128) % 255;
        int g = (cpixels[cursorY][cursorX].g + 128) % 255;
        int b = (cpixels[cursorY][cursorX].b + 128) % 255;
        int br = (cpixels[cursorY][cursorX].br + 128) % 255;
        int bg = (cpixels[cursorY][cursorX].bg + 128) % 255;
        int bb = (cpixels[cursorY][cursorX].bb + 128) % 255;
        gfx->setForeColor(r, g, b, 255, x, y);
        gfx->setBackColor(br, bg, bb, 255, x, y);
    }
}

int Sketchpad::getCursorX() const { return cursorX; }

int Sketchpad::getCursorY() const { return cursorY; }

Cpixel Sketchpad::getCellInfo(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return {};
    } else {
        return cpixels[y][x];
    }
}
