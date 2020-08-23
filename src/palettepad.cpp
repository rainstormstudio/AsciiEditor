#include "palettepad.hpp"

Palettepad::Palettepad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height) 
    : Panel(app, top, left, width, height) {
    palette = std::vector<std::vector<Color>>(18);
    for (unsigned int i = 0; i < 18; ++i) {
        palette[i] = std::vector<Color>(18);
        palette[i][0] = {255, 0, 0, static_cast<Uint8>(255 * i / 18)};
        palette[i][1] = {255, 0, 128, static_cast<Uint8>(255 * i / 18)};
        palette[i][2] = {255, 0, 255, static_cast<Uint8>(255 * i / 18)};
        palette[i][3] = {128, 0, 255, static_cast<Uint8>(255 * i / 18)};
        palette[i][4] = {0, 0, 255, static_cast<Uint8>(255 * i / 18)};
        palette[i][5] = {0, 128, 255, static_cast<Uint8>(255 * i / 18)};
        palette[i][6] = {0, 255, 255, static_cast<Uint8>(255 * i / 18)};
        palette[i][7] = {0, 255, 128, static_cast<Uint8>(255 * i / 18)};
        palette[i][8] = {0, 255, 0, static_cast<Uint8>(255 * i / 18)};
        palette[i][9] = {128, 255, 0, static_cast<Uint8>(255 * i / 18)};
        palette[i][10] = {255, 255, 0, static_cast<Uint8>(255 * i / 18)};
        palette[i][11] = {255, 128, 0, static_cast<Uint8>(255 * i / 18)};
        palette[i][12] = {245, 245, 245, static_cast<Uint8>(255 * i / 18)};
        palette[i][13] = {247, 247, 247, static_cast<Uint8>(255 * i / 18)};
        palette[i][14] = {249, 249, 249, static_cast<Uint8>(255 * i / 18)};
        palette[i][15] = {251, 251, 251, static_cast<Uint8>(255 * i / 18)};
        palette[i][16] = {253, 253, 253, static_cast<Uint8>(255 * i / 18)};
        palette[i][17] = {255, 255, 255, static_cast<Uint8>(255 * i / 18)};
    }
    selectedFore = 18 * 18 - 1;
    selectedBack = 0;
    selectedForeColor = palette[selectedFore / 18][selectedFore % 18];
    selectedBackColor = palette[selectedBack / 18][selectedBack % 18];
}

void Palettepad::update() {
    updateCursor();
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (cursorX - 1 >= 0 && cursorX - 1 < 18
            && cursorY - 1 >= 0 && cursorY - 1 < 18) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                selectedFore = (cursorY - 1) * 18 + (cursorX - 1);
            } else if (event->button.button == SDL_BUTTON_RIGHT) {
                selectedBack = (cursorY - 1) * 18 + (cursorX - 1);
            }
        }
    }
    selectedForeColor = palette[selectedFore / 18][selectedFore % 18];
    selectedBackColor = palette[selectedBack / 18][selectedBack % 18];
}

void Palettepad::render() {
    drawBorder("PALETTE");
    fillBackColor(40, 90, 80, 255);
    fillForeColor(0, 255, 255, 255);
    for (unsigned int i = 0; i < 18; ++i) {
        for (unsigned int j = 0; j < 18; ++j) {
            gfx->setBackColor(palette[i][j].r, palette[i][j].g, palette[i][j].b, palette[i][j].a, j + left + 1, i + top + 1);
            int r = palette[i][j].r > 128 ? 0 : 255;
            int g = palette[i][j].g > 128 ? 0 : 255;
            int b = palette[i][j].b > 128 ? 0 : 255;
            int a = 255;
            gfx->setForeColor(r, g, b, a, j + left + 1, i + top + 1);
            if (i == selectedFore / 18 && j == selectedFore % 18
                && i == selectedBack / 18 && j == selectedBack % 18) {
                gfx->setCh('*', j + left + 1, i + top + 1);
            } else if (i == selectedFore / 18 && j == selectedFore % 18) {
                gfx->setCh('f', j + left + 1, i + top + 1);
            } else if (i == selectedBack / 18 && j == selectedBack % 18) {
                gfx->setCh('b', j + left + 1, i + top + 1);
            }
        }
    }
    if (cursorX != -1 && cursorY != -1) {
        int x = cursorX + left;
        int y = cursorY + top;
        if (y - 1 > top && x > left && x < left + width - 1) {
            gfx->setCh('|', x, y - 1);
        }
        if (y + 2 < height + top) {
            if (x - 1 > left + 1) {
                gfx->setCh('/', x - 1, y + 1);
            }
            if (x + 2 < left + width) {
                gfx->setCh('\\', x + 1, y + 1);
            }
        }
    }
}

Color Palettepad::getForeColor() const {
    return selectedForeColor;
}

Color Palettepad::getBackColor() const {
    return selectedBackColor;
}
