#ifndef FILEPAD_HPP
#define FILEPAD_HPP

#include "panel.hpp"

class Button;

class Filepad : public Panel {
    Button* newButton;
    Button* saveButton;
    Button* loadButton;
public:
    Filepad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height);
    ~Filepad();
    bool newClicked() const;
    bool saveClicked() const;
    bool loadClicked() const;
    void update() override;
    void render() override;
};

#endif
