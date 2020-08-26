#include "application.hpp"
#include "commandHistory.hpp"
#include "command.hpp"
#include "undoCommand.hpp"
#include "brushDownCommand.hpp"
#include "brushUpCommand.hpp"
#include "drawCommand.hpp"
#include "drawPosCommand.hpp"
#include "fillCommand.hpp"
#include "newFileCommand.hpp"
#include "saveFileCommand.hpp"
#include "loadFileCommand.hpp"
#include <memory>

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
    toolpad = new Toolpad(this, 47, 8, 12, 9);

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
                        executeCommand(std::make_shared<BrushDownCommand>(this, sketchpad));
                    } else if (toolpad->getSelected() == 2) {
                        executeCommand(std::make_shared<FillCommand>(this, sketchpad));
                    }
                }
            }
        } else if (event->type == SDL_MOUSEBUTTONUP) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (sketchpad->validPos()) {
                    executeCommand(std::make_shared<BrushUpCommand>(this, sketchpad));
                }
            }
        } else if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_z && SDL_GetModState() & KMOD_CTRL) {
                executeCommand(std::make_shared<UndoCommand>(this, sketchpad));
            } else if (event->key.keysym.sym == SDLK_n && SDL_GetModState() & KMOD_CTRL) {
                executeCommand(std::make_shared<NewFileCommand>(this, sketchpad));
            } else if (event->key.keysym.sym == SDLK_s && SDL_GetModState() & KMOD_CTRL) {
                executeCommand(std::make_shared<SaveFileCommand>(this, sketchpad));
            }
        }
    }
    if (sketchpad->validPos() && sketchpad->getBrush()) {
        if (toolpad->getSelected() == 0) {
            executeCommand(std::make_shared<DrawCommand>(this, sketchpad));
        } else if (toolpad->getSelected() == 1) {
            Cpixel blank = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            executeCommand(std::make_shared<DrawPosCommand>(this, sketchpad, blank, sketchpad->getCursorX(), sketchpad->getCursorY()));
        }
    }
    if (editpad->undo()) {
        executeCommand(std::make_shared<UndoCommand>(this, sketchpad));
    }
    if (filepad->newClicked()) {
        executeCommand(std::make_shared<NewFileCommand>(this, sketchpad));
    }
    if (filepad->saveClicked()) {
        executeCommand(std::make_shared<SaveFileCommand>(this, sketchpad));
    }
    if (filepad->loadClicked()) {
        executeCommand(std::make_shared<LoadFileCommand>(this, sketchpad));
    }
}

Graphics* Application::getGFX() const { return gfx; }

SDL_Event* Application::getEvent() const { return event; }

void Application::executeCommand(std::shared_ptr<Command> command) {
    if (command->execute()) {
        history->push(command);
    }
}

void Application::undo() {
    std::shared_ptr<Command> command = history->pop();
    while (command && !std::dynamic_pointer_cast<BrushDownCommand>(command)) {
        command->undo();
        command = history->pop();
    }
}
