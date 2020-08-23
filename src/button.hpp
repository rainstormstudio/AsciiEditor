#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "command.hpp"
#include "panel.hpp"

class Application;

class Button : public Panel {
    std::string content;
    Uint32 last;
    bool pressed;
public:
    Button(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, std::string content);
    bool hasPressed() const;
    void update() override;
    void render() override;
};

#endif
