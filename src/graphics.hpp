#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "ctexture.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <memory>

class Graphics {
    std::string title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Texture* tileset;
    unsigned int numSrcRows;
    unsigned int numSrcCols;
    unsigned int tileWidth;
    unsigned int tileHeight;

    Uint32 fullscreen;
    unsigned int screenWidth;
    unsigned int screenHeight;

    unsigned int numRows;
    unsigned int numCols;
    std::vector<std::vector<std::shared_ptr<CTexture>>> textDisplay;

public:
    Graphics(std::string title, std::string tilesetFilename, 
             unsigned int numSrcRows, unsigned int numSrcCols,
             Uint32 fullscreenFlag, std::string fontPath,
             unsigned int screenWidth, unsigned int screenHeight,
             unsigned int numRows, unsigned int numCols);
    ~Graphics();

    void setCh(char index, int x, int y);
    void setForeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y);
    void setBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y);
    void importTxt(std::string filename, bool transparent);

    void write(std::string content, int x, int y);
    void write(std::string content, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void write(std::string content, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba);

    void writeln(std::string content, int x, int y, int width);
    void writeln(std::string content, int x, int y, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void writeln(std::string content, int x, int y, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba);

    void clear();
    void render();
};

#endif
