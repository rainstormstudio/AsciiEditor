#ifndef TOOLPAD_HPP
#define TOOLPAD_HPP

#include "panel.hpp"

class Toolpad : public Panel {
    unsigned int selected;
public:
    Toolpad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height);
    void update() override;
    void render() override;

    unsigned int getSelected() const;
};

#endif
