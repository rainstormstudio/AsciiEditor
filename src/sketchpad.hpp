#ifndef SKETCHPAD_HPP
#define SKETCHPAD_HPP

#include <vector>
#include "panel.hpp"
#include "charpad.hpp"
#include "palettepad.hpp"

struct Cpixel {
    Uint8 ch;
    Uint8 r, g, b, a;
    Uint8 br, bg, bb, ba;
};

class Sketchpad : public Panel {
    Charpad* charpad;
    Palettepad* palettepad;
    int cursorX;
    int cursorY;
    std::vector<std::vector<Cpixel>> cpixels;
    bool brushDown;

public:
    Sketchpad(Graphics* gfx, SDL_Event* event, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Charpad* charpad, Palettepad* palettepad);
    void drawPoint(Uint8 ch, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba);
    void update() override;
    void render() override;

    int getCursorX() const;
    int getCursorY() const;

    Cpixel getCellInfo(int x, int y) const;
};

#endif
