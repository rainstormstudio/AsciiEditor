#include "sketchpad.hpp"

Sketchpad::Sketchpad(Graphics* gfx, SDL_Event* event, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Charpad* charpad, Palettepad* palettepad)
    : Panel(gfx, event, top, left, width, height), charpad{charpad}, palettepad{palettepad} {
    cpixels = std::vector<std::vector<Cpixel>>(height);
    for (unsigned int i = 0; i < height; ++i) {
        cpixels[i] = std::vector<Cpixel>(width);
        for (unsigned int j = 0; j < width; ++j) {
            cpixels[i][j] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        }
    }
    cursorX = 0;
    cursorY = 0;
    brushDown = false;
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
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            brushDown = true;
        }
    } else if (event->type == SDL_MOUSEBUTTONUP) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            brushDown = false;
        }
    }
    if (brushDown) {
        if (cursorX >= 0 && cursorX < width
            && cursorY >= 0 && cursorY < height) {
            Color foreColor = palettepad->getForeColor();
            Color backColor = palettepad->getBackColor();
            cpixels[cursorY][cursorX] = {charpad->getSelected(), 
                                        foreColor.r, 
                                        foreColor.g, 
                                        foreColor.b, 
                                        foreColor.a, 
                                        backColor.r, 
                                        backColor.g, 
                                        backColor.b, 
                                        backColor.a};
        }
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
        int r = cpixels[cursorY][cursorX].r > 128 ? 0 : 255;
        int g = cpixels[cursorY][cursorX].g > 128 ? 0 : 255;
        int b = cpixels[cursorY][cursorX].b > 128 ? 0 : 255;
        int br = cpixels[cursorY][cursorX].br > 128 ? 0 : 255;
        int bg = cpixels[cursorY][cursorX].bg > 128 ? 0 : 255;
        int bb = cpixels[cursorY][cursorX].bb > 128 ? 0 : 255;
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
