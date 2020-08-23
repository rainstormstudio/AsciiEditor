#include "statuspad.hpp"

std::string Statuspad::prefix(char ch, std::string str, int width) {
    if (width <= str.length()) {
        return str;
    } else {
        for (int i = 0; i < width - str.length() + 1; ++i) {
            str = ch + str;
        }
        return str;
    }
}

Statuspad::Statuspad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Sketchpad* sketchpad)
    : Panel(app, top, left, width, height), sketchpad{sketchpad} {
}

void Statuspad::update() {
}

void Statuspad::render() {
    drawBorder("STATUS");
    fillBackColor(40, 90, 80, 255);
    fillForeColor(0, 255, 255, 255);
    int x = sketchpad->getCursorX();
    int y = sketchpad->getCursorY();
    Cpixel cpixel = sketchpad->getCellInfo(x, y);
    if (x != -1 && y != -1) {
        gfx->write("x: " + prefix(' ', std::to_string(x), 2), left + 1, top + 1);
        gfx->write("y: " + prefix(' ', std::to_string(y), 2), left + 7, top + 1);
        gfx->write("char: ", left + 1, top + 2);
        gfx->setCh(cpixel.ch, left + 6, top + 2);
        gfx->write("fRGB(" + prefix('0', std::to_string(cpixel.r), 3) + "," + 
                            prefix('0', std::to_string(cpixel.g), 3) + "," + 
                            prefix('0', std::to_string(cpixel.b), 3) + ")", left + 1, top + 3);
        gfx->setBackColor(cpixel.r, cpixel.g, cpixel.b, cpixel.a, left + width - 2, top + 3);
        gfx->write("bRGB(" + prefix('0', std::to_string(cpixel.br), 3) + "," + 
                            prefix('0', std::to_string(cpixel.bg), 3) + "," + 
                            prefix('0', std::to_string(cpixel.bb), 3) + ")", left + 1, top + 4);
        gfx->setBackColor(cpixel.br, cpixel.bg, cpixel.bb, cpixel.ba, left + width - 2, top + 4);
    } else {
        gfx->write("x: -", left + 1, top + 1);
        gfx->write("y: -", left + 7, top + 1);
        gfx->write("char: ", left + 1, top + 2);
        gfx->write("fRGB(---,---,---)", left + 1, top + 3);
        gfx->write("bRGB(---,---,---)", left + 1, top + 4);
    }
}
