#include "graphics.hpp"
#include "SDL2/SDL.h"

#include <iostream>

int main(int argc, char* argv[]) {
    Graphics * gfx = new Graphics("AsciiEditor", 0, 800, 600, 30, 80);

    gfx->clear();
    gfx->setCh('@', 2, 1);
    gfx->setColor(0, 100, 255, 255, 2, 1);
    gfx->render();
    
    char ch;
    std::cin >> ch;

    gfx->clear();
    gfx->setCh('2', 3, 1);
    gfx->setColor(255, 100, 0, 255, 3, 1);
    gfx->render();

    std::cin >> ch;

    delete gfx;
    return 0;
}