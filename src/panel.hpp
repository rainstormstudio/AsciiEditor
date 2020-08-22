#ifndef PANEL_HPP
#define PANEL_HPP

#include "graphics.hpp"

class Panel {
protected:
    Graphics* gfx;
    SDL_Event* event;
    unsigned int top;
    unsigned int left;
    unsigned int width;
    unsigned int height;
public:
    Panel(Graphics* gfx, SDL_Event* event, unsigned int top, unsigned int left, unsigned int width, unsigned int height);
    void drawBorder(std::string title);
    void fillBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void fillForeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    virtual void update() = 0;
    virtual void render() = 0;

    unsigned int getTop() const;
    unsigned int getLeft() const;
};

#endif
