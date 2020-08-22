#ifndef STATUSPAD_HPP
#define STATUSPAD_HPP

#include "panel.hpp"
#include "sketchpad.hpp"

class Statuspad : public Panel {
    Sketchpad* sketchpad;
public:
    Statuspad(Graphics * gfx, SDL_Event* event, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Sketchpad* sketchpad);
    void update() override;
    void render() override;
};

#endif
