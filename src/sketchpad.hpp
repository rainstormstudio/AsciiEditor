#ifndef SKETCHPAD_HPP
#define SKETCHPAD_HPP

#include <vector>
#include "panel.hpp"
#include "charpad.hpp"
#include "palettepad.hpp"
#include <fstream>

struct Cpixel {
    Uint8 ch;
    Uint8 r, g, b, a;
    Uint8 br, bg, bb, ba;
    bool operator==(const Cpixel& other) {
        return (ch == other.ch 
            && r == other.r
            && g == other.g
            && b == other.b
            && a == other.a
            && br == other.br
            && bg == other.bg
            && ba == other.ba);
    }
};

class Sketchpad : public Panel {
    Charpad* charpad;
    Palettepad* palettepad;
    std::vector<std::vector<Cpixel>> cpixels;
    bool brushDown;

    void fill(Cpixel prevColor, Cpixel newColor, int x, int y);

public:
    Sketchpad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, Charpad* charpad, Palettepad* palettepad);
    void drawPoint();
    void drawPoint(Cpixel info, int x, int y);
    void fillArea();
    void fillArea(Cpixel info, int x, int y);
    void update() override;
    void render() override;

    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);

    void setBrush(bool down);
    bool getBrush() const;

    int getCursorX() const;
    int getCursorY() const;

    Cpixel getCellInfo(int x, int y) const;
};

#endif
