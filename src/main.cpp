#include "graphics.hpp"
#include "sketchpad.hpp"
#include "statuspad.hpp"
#include "SDL2/SDL.h"

#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    Graphics* gfx = new Graphics("AsciiEditor", "./assets/tilesets/Vintl01.png", 16, 16, 0, "./assets/fonts/Monaco.ttf", 1280, 960, 60, 80);
    SDL_Event event;
    Sketchpad* sketchpad = new Sketchpad(gfx, &event, 0, 20, 60, 60);
    Statuspad* statuspad = new Statuspad(gfx, &event, 0, 0, 20, 5, sketchpad);

    bool loop = true;
    while (loop) {
        sketchpad->update();

        gfx->clear();
        sketchpad->render();

        int x = 0, y = 0;
        for (unsigned int i = 0; i < 16 * 16; ++i) {
            if (i > 0 && i % 16 == 0) {
                x = 0;
                ++y;
            }
            sketchpad->drawPoint(i, x, y, 0, 0, 0, 255, 100, 100, 100, 255);
            ++x;            
        }

        statuspad->render();
        gfx->render();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                loop = false;                
            }
        }
    }

    delete sketchpad;
    delete gfx;
    return 0;
}