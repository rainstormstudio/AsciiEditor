#include "graphics.hpp"
#include "SDL2/SDL.h"

#include <iostream>

int main(int argc, char* argv[]) {
    Graphics * gfx = new Graphics("", 0, 800, 600, 30, 80);

    gfx->render();
    
    char ch;
    std::cin >> ch;

    delete gfx;
    return 0;
}