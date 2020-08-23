#include "button.hpp"
#include "application.hpp"

Button::Button(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Command* command, std::string content) 
    : Panel(app, top, left, width, height), command{command}, content{content} {
    last = 0;
}

void Button::update() {
    updateCursor();
    if (cursorX != -1 && cursorY != -1) {
        if (last == SDL_MOUSEBUTTONDOWN && event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
            app->executeCommand(command);
        }
    }
    last = event->type;
}

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
