#ifndef EDITPAD_HPP
#define EDITPAD_HPP

#include "panel.hpp"

class Button;
class Command;

class Editpad : public Panel {
    Button* undoButton;
public:
    Editpad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Command* undo);
    ~Editpad();
    void update() override;
    void render() override;
};

#endif
