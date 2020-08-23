#include "sketchpad.hpp"
#include "application.hpp"
#include "brushDownCommand.hpp"
#include "brushUpCommand.hpp"
#include "drawCommand.hpp"
#include "drawPosCommand.hpp"

void Sketchpad::fill(Cpixel prevColor, Cpixel newColor, int x, int y) {
    if (!(x >= 0 && x < width && y >= 0 && y < height)) {
        return;        
    }
    if (!(cpixels[y][x] == prevColor)) {
        return;
    }
    if (cpixels[y][x] == newColor) {
        return;
    }
    app->executeCommand(new DrawPosCommand(app, this, newColor, x, y));
    fill(prevColor, newColor, x - 1, y);
    fill(prevColor, newColor, x + 1, y);
    fill(prevColor, newColor, x, y - 1);
    fill(prevColor, newColor, x, y + 1);
}

Sketchpad::Sketchpad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Charpad* charpad, Palettepad* palettepad)
    : Panel(app, top, left, width, height), charpad{charpad}, palettepad{palettepad} {
    cpixels = std::vector<std::vector<Cpixel>>(height);
    for (unsigned int i = 0; i < height; ++i) {
        cpixels[i] = std::vector<Cpixel>(width);
        for (unsigned int j = 0; j < width; ++j) {
            cpixels[i][j] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        }
    }
    brushDown = false;
}

void Sketchpad::drawPoint() {
    if (cursorX != -1 && cursorY != -1) {
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

void Sketchpad::drawPoint(Cpixel info, int x, int y) {
    if (x != -1 && y != -1) {
        cpixels[y][x] = info;
    }
}

void Sketchpad::fillArea() {
    if (cursorX != -1 && cursorY != -1) {
        app->executeCommand(new BrushDownCommand(app, this));
        Color foreColor = palettepad->getForeColor();
        Color backColor = palettepad->getBackColor();
        fill(cpixels[cursorY][cursorX], 
                {charpad->getSelected(), 
                foreColor.r, 
                foreColor.g, 
                foreColor.b, 
                foreColor.a, 
                backColor.r, 
                backColor.g, 
                backColor.b, 
                backColor.a}, 
                cursorX, cursorY);
        app->executeCommand(new BrushUpCommand(app, this));
    }
}

void Sketchpad::fillArea(Cpixel info, int x, int y) {
    if (x != -1 && y != -1) {
        fill(info, cpixels[cursorY][cursorX], x, y);
    }
}

void Sketchpad::update() {
    updateCursor();
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

void Sketchpad::saveToFile(std::string filename) {
    std::ofstream outfile{filename};
    if (outfile.is_open()) {
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                outfile << "("
                        << cpixels[i][j].ch << ","
                        << cpixels[i][j].r << ","
                        << cpixels[i][j].g << ","
                        << cpixels[i][j].b << ","
                        << cpixels[i][j].a << ","
                        << cpixels[i][j].br << ","
                        << cpixels[i][j].bg << ","
                        << cpixels[i][j].bb << ","
                        << cpixels[i][j].ba << ")";
            }
            outfile << std::endl;
        }
    } else {
        std::cerr << "Error saving file to " << filename << std::endl;
    }
}

void Sketchpad::loadFromFile(std::string filename) {
    //TODO: implement loadFromFile
}

void Sketchpad::setBrush(bool down) {
    brushDown = down;
}

bool Sketchpad::getBrush() const {
    return brushDown;
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
