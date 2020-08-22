#ifndef STATUSPAD_HPP
#define STATUSPAD_HPP

#include "panel.hpp"

class Statuspad : public Panel {
public:
    Statuspad(Graphics * gfx, unsigned int top, unsigned int left, unsigned int width, unsigned int height);
    void render() override;
};

#endif
