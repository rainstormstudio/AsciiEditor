#include "graphics.hpp"
#include "SDL2/SDL.h"

#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    Graphics * gfx = new Graphics("AsciiEditor", 0, "./assets/fonts/Monaco.ttf", 800, 600, 30, 80);

    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 100; ++j) {
            gfx->clear();
            for (int k = 0; k < 10; ++k) {
                for (int l = 0; l < 20; ++l) {
                    gfx->setCh('@', j-k-l, 17-k);
                    gfx->setForeColor(round(255.0 * (j-20) / 50.0), 
                                      int(round(500.0 - 500.0 * (j-20) / 50.0)) % 255, 
                                      255 - int(round(500.0 - 500.0 * (j-20) / 50.0)) % 255, 
                                      int(round(255.0 - 255.0 * double(l) / 20.0)), 
                                      j-k-l, 17-k);
                }
            }
            gfx->importTxt("./assets/txt/test.txt", true);
            gfx->render();
        }
    }
    gfx->clear();
    gfx->importTxt("./assets/txt/test2.txt", true);
    gfx->render();
    char ch;
    std::cin >> ch;
    delete gfx;
    return 0;
}