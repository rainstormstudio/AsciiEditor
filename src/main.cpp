#include "graphics.hpp"
#include "charpad.hpp"
#include "palettepad.hpp"
#include "sketchpad.hpp"
#include "statuspad.hpp"
#include "SDL2/SDL.h"

#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    Graphics* gfx = new Graphics("AsciiEditor", "./assets/tilesets/Vintl01.png", 16, 16, 0, "./assets/fonts/Monaco.ttf", 1280, 960, 60, 80);
    SDL_Event event;
    Charpad* charpad = new Charpad(gfx, &event, 6, 0, 20, 20);
    Palettepad* palettepad = new Palettepad(gfx, &event, 26, 0, 20, 20);
    Sketchpad* sketchpad = new Sketchpad(gfx, &event, 0, 20, 60, 60, charpad, palettepad);
    Statuspad* statuspad = new Statuspad(gfx, &event, 0, 0, 20, 6, sketchpad);

    bool loop = true;
    while (loop) {
        charpad->update();
        palettepad->update();
        sketchpad->update();

        gfx->clear();
        sketchpad->render();
        charpad->render();
        palettepad->render();
        statuspad->render();

        gfx->render();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                loop = false;                
            }
        }
    }

    delete sketchpad;
    delete statuspad;
    delete charpad;
    delete gfx;
    return 0;
}