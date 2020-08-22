#include "sketchpad.hpp"

Sketchpad::Sketchpad(Graphics* gfx, unsigned int top, unsigned int left, unsigned int width, unsigned int height)
    : Panel(gfx, top, left, width, height) {
    cpixels = std::vector<std::vector<Cpixel>>(height);
    for (unsigned int i = 0; i < height; ++i) {
        cpixels[i] = std::vector<Cpixel>(width);
        for (unsigned int j = 0; j < width; ++j) {
            cpixels[i][j] = {'0', 0, 0, 0, 0, 100, 100, 100, 255};
        }
    }
}

void Sketchpad::drawPoint(char ch, int x, int y, Uint8 r , Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    cpixels[y][x] = {ch, r, g, b, a, br, bg, bb, ba};
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
}
