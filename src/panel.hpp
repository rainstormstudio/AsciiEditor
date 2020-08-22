#ifndef PANEL_HPP
#define PANEL_HPP

#include "graphics.hpp"

class Panel {
protected:
    Graphics* gfx;
    unsigned int top;
    unsigned int left;
public:
    Panel(Graphics* gfx, unsigned int top, unsigned int left);
};

#endif
