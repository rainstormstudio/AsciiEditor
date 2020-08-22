#include "graphics.hpp"
#include "sketchpad.hpp"
#include "SDL2/SDL.h"

#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    Graphics* gfx = new Graphics("AsciiEditor", "./assets/tilesets/Vintl01.png", 16, 16, 0, "./assets/fonts/Monaco.ttf", 1280, 960, 60, 80);
    Sketchpad* sketchpad = new Sketchpad(gfx, 0, 20, 60, 60);
    SDL_Event event;

    bool loop = true;
    while (loop) {
        gfx->clear();
        sketchpad->render();
        gfx->render();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                loop = false;                
            }
        }
    }

    delete gfx;
    return 0;
}