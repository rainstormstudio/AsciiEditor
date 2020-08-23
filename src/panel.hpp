#ifndef PANEL_HPP
#define PANEL_HPP

#include "graphics.hpp"

class Application;

class Panel {
protected:
    Application* app;
    Graphics* gfx;
    SDL_Event* event;
    unsigned int top;
    unsigned int left;
    unsigned int width;
    unsigned int height;

    int cursorX;
    int cursorY;
public:
    Panel(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height);
    void drawBorder(std::string title);
    void fillBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void fillForeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void updateCursor();

    virtual void update() = 0;
    virtual void render() = 0;

    bool validPos() const;

    unsigned int getTop() const;
    unsigned int getLeft() const;
};

#endif
