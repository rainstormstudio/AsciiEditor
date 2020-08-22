#ifndef SKETCHPAD_HPP
#define SKETCHPAD_HPP

#include <vector>
#include "panel.hpp"

struct Cpixel {
    char ch;
    Uint8 r, g, b, a;
    Uint8 br, bg, bb, ba;
};

class Sketchpad : public Panel {
    std::vector<std::vector<Cpixel>> cpixels;

public:
    Sketchpad(Graphics* gfx, unsigned int top, unsigned int left, unsigned int width, unsigned int height);
    void drawPoint(char ch, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba);
    void render() override;
};

#endif
