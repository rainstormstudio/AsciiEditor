#include "application.hpp"
#include "commandHistory.hpp"
#include "command.hpp"
#include "undoCommand.hpp"
#include "brushDownCommand.hpp"
#include "brushUpCommand.hpp"
#include "drawCommand.hpp"
#include "drawPosCommand.hpp"
#include "fillCommand.hpp"

Application::Application() {
    gfx = new Graphics("AsciiEditor", "./assets/tilesets/Vintl01.png", 16, 16, 0, "./assets/fonts/Monaco.ttf", 1280, 960, 60, 80);
    event = new SDL_Event();
    history = new CommandHistory();
    charpad = new Charpad(this, 7, 0, 20, 20);
    palettepad = new Palettepad(this, 27, 0, 20, 20);
    sketchpad = new Sketchpad(this, 0, 20, 60, 60, charpad, palettepad);
    statuspad = new Statuspad(this, 0, 0, 20, 7, sketchpad);
    editpad = new Editpad(this, 47, 0, 8, 4);
    filepad = new Filepad(this, 51, 0, 8, 5);
    toolpad = new Toolpad(this, 47, 8, 12, 8);

    running = true;
}

Application::~Application() {
    delete toolpad;
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
    toolpad->update();
}

void Application::render() {
    gfx->clear();
    sketchpad->render();
    charpad->render();
    palettepad->render();
    statuspad->render();
    editpad->render();
    filepad->render();
    toolpad->render();
    gfx->render();
}

void Application::processInput() {
    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            running = false;
        } else if (event->type == SDL_MOUSEBUTTONDOWN) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (sketchpad->validPos()) {
                    if (toolpad->getSelected() == 0 || toolpad->getSelected() == 1) {
                        executeCommand(new BrushDownCommand(this, sketchpad));
                    } else if (toolpad->getSelected() == 2) {
                        executeCommand(new FillCommand(this, sketchpad));
                    }
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
        if (toolpad->getSelected() == 0) {
            executeCommand(new DrawCommand(this, sketchpad));
        } else if (toolpad->getSelected() == 1) {
            executeCommand(new DrawPosCommand(this, sketchpad, {0, 0, 0, 0, 0, 0, 0, 0, 0}, sketchpad->getCursorX(), sketchpad->getCursorY()));
        }
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
