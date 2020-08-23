#include "button.hpp"
#include "application.hpp"

Button::Button(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, std::string content) 
    : Panel(app, top, left, width, height), content{content} {
    last = 0;
    pressed = false;
}

void Button::update() {
    updateCursor();
    pressed = false;
    if (cursorX != -1 && cursorY != -1) {
        if (last == SDL_MOUSEBUTTONDOWN && event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
            pressed = true;
        }
    }
    last = event->type;
}

bool Button::hasPressed() const { return pressed; }

void Button::render() {
    gfx->write("[" + content + "]", left, top);
    if (cursorX != -1 && cursorY != -1) {
        if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
            fillForeColor(55, 120, 170, 255);
            fillBackColor(80, 170, 55, 255);
        } else {
            fillForeColor(80, 170, 55, 255);
            fillBackColor(255, 170, 75, 255);
        }
    } else {
        fillForeColor(100, 130, 255, 255);
        fillBackColor(20, 55, 60, 255);
    }
}
