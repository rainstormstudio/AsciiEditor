#ifndef PALETTEPAD_HPP
#define PALETTEPAD_HPP

#include "panel.hpp"

struct Color {
    Uint8 r, g, b, a;
};

class Palettepad : public Panel {
    unsigned int selectedFore;
    unsigned int selectedBack;
    Color selectedForeColor;
    Color selectedBackColor;
    std::vector<std::vector<Color>> palette;
public:
    Palettepad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height);
    void update() override;
    void render() override;

    Color getForeColor() const;
    Color getBackColor() const;
};

#endif
