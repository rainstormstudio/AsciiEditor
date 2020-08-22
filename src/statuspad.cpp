#include "statuspad.hpp"

Statuspad::Statuspad(Graphics* gfx, unsigned int top, unsigned int left, unsigned int width, unsigned int height)
    : Panel(gfx, top, left, width, height) {}

void Statuspad::render() {
    drawBorder("STATUS");
    fillBackColor(40, 90, 80, 255);
}
