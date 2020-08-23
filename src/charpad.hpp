#ifndef CHARPAD_HPP
#define CHARPAD_HPP

#include "panel.hpp"

class Charpad : public Panel {
    Uint8 selected;
public:
    Charpad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height);
    void update() override;
    void render() override;

    Uint8 getSelected() const;
};

#endif
