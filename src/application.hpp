#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "graphics.hpp"
#include "charpad.hpp"
#include "palettepad.hpp"
#include "sketchpad.hpp"
#include "statuspad.hpp"
#include "editpad.hpp"
#include "filepad.hpp"
#include "SDL2/SDL.h"

class CommandHistory;
class Command;

class Application {
    CommandHistory* history;

    Graphics* gfx;
    SDL_Event* event;
    Charpad* charpad;
    Palettepad* palettepad;
    Sketchpad* sketchpad;
    Statuspad* statuspad;
    Editpad* editpad;
    Filepad* filepad;

    bool running;

public:
    Application();
    ~Application();
    bool isRunning() const;
    void update();
    void render();
    void processInput();

    Graphics* getGFX() const;
    SDL_Event* getEvent() const;

    void executeCommand(Command* command);
    void undo();
};

#endif
