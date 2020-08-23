#ifndef STATUSPAD_HPP
#define STATUSPAD_HPP

#include "panel.hpp"
#include "sketchpad.hpp"

class Statuspad : public Panel {
    Sketchpad* sketchpad;

    std::string prefix(char ch, std::string str, int width);
public:
    Statuspad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Sketchpad* sketchpad);
    void update() override;
    void render() override;
};

#endif
