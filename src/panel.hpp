#ifndef PANEL_HPP
#define PANEL_HPP

#include "graphics.hpp"

class Panel {
protected:
    Graphics* gfx;
    unsigned int top;
    unsigned int left;
    unsigned int width;
    unsigned int height;
public:
    Panel(Graphics* gfx, unsigned int top, unsigned int left, unsigned int width, unsigned int height);
    void drawBorder(std::string title);
    void fillBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    virtual void render() = 0;
};

#endif
