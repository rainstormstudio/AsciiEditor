#include "application.hpp"
#include "commandHistory.hpp"
#include "command.hpp"
#include "undoCommand.hpp"
#include "brushDownCommand.hpp"
#include "brushUpCommand.hpp"
#include "drawCommand.hpp"

Application::Application() {
    gfx = new Graphics("AsciiEditor", "./assets/tilesets/Vintl01.png", 16, 16, 0, "./assets/fonts/Monaco.ttf", 1280, 960, 60, 80);
    event = new SDL_Event();
    history = new CommandHistory();
    charpad = new Charpad(this, 7, 0, 20, 20);
    palettepad = new Palettepad(this, 27, 0, 20, 20);
    sketchpad = new Sketchpad(this, 0, 20, 60, 60, charpad, palettepad);
    statuspad = new Statuspad(this, 0, 0, 20, 7, sketchpad);
    editpad = new Editpad(this, 47, 0, 10, 4);
    filepad = new Filepad(this, 51, 0, 10, 5);

    running = true;
}

Application::~Application() {
    delete filepad;
    delete editpad;
    delete statuspad;
    delete sketchpad;
    delete palettepad;
    delete charpad;
    delete history;
    delete event;
    delete gfx;
}

bool Application::isRunning() const { return running; }

void Application::update() {
    charpad->update();
    palettepad->update();
    sketchpad->update();
    editpad->update();
    filepad->update();
}

void Application::render() {
    gfx->clear();
    sketchpad->render();
    charpad->render();
    palettepad->render();
    statuspad->render();
    editpad->render();
    filepad->render();
    gfx->render();
}

void Application::processInput() {
    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            running = false;
        } else if (event->type == SDL_MOUSEBUTTONDOWN) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (sketchpad->validPos()) {
                    executeCommand(new BrushDownCommand(this, sketchpad));
                }
            }
        } else if (event->type == SDL_MOUSEBUTTONUP) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (sketchpad->validPos()) {
                    executeCommand(new BrushUpCommand(this, sketchpad));
                }
            }
        }
    }
    if (sketchpad->validPos() && sketchpad->getBrush()) {
        executeCommand(new DrawCommand(this, sketchpad));
    }
    if (editpad->undo()) {
        executeCommand(new UndoCommand(this, sketchpad));
    }
}

Graphics* Application::getGFX() const { return gfx; }

SDL_Event* Application::getEvent() const { return event; }

void Application::executeCommand(Command* command) {
    if (command->execute()) {
        history->push(command);
    }
}

void Application::undo() {
    Command* command = history->pop();
    while (command && !dynamic_cast<BrushDownCommand*>(command)) {
        command->undo();
        command = history->pop();
    }
}
