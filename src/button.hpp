#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "command.hpp"
#include "panel.hpp"

class Application;

class Button : public Panel {
    Command* command;
    std::string content;
    Uint32 last;
public:
    Button(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Command* command, std::string content);
    void update() override;
    void render() override;
};

#endif
