#ifndef TEXTINPUTPAD_HPP
#define TEXTINPUTPAD_HPP

#include "panel.hpp"

class Button;

class TextInputpad : public Panel {
    std::string title;
    std::string text;
    Button* okButton;
    Button* cancelButton;
    bool done;
public:
    TextInputpad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, std::string title);
    std::string getText() const;
    void update() override;
    void render() override;
};

#endif
