#include "textInputpad.hpp"
#include "application.hpp"
#include "quitException.hpp"
#include "button.hpp"

TextInputpad::TextInputpad(Application* app, unsigned int top, unsigned int left, unsigned int width, unsigned int height, std::string title)
    : Panel(app, top, left, width, height), title{title} {
    text = "";
    SDL_Event* event = app->getEvent();
    okButton = new Button(app, top + height - 2, left + 1, 8, 1, "  ok  ");
    cancelButton = new Button(app, top + height - 2, left + 11, 8, 1, "cancel");
    SDL_StartTextInput();
    done = false;
    while (!done) {
        try {
            update();
        } catch (QuitException) {
            throw;
            return;
        }
        okButton->update();
        cancelButton->update();
        if (okButton->hasPressed()) {
            done = true;
            break;
        }
        if (cancelButton->hasPressed()) {
            break;
        }

        app->getGFX()->clear();
        render();
        okButton->render();
        cancelButton->render();
        app->getGFX()->render();
    }
    SDL_StopTextInput();
}

std::string TextInputpad::getText() const {
    if (done) {
        return text;
    } else {
        return "";
    }
}

void TextInputpad::update() {
    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            throw QuitException();
        } else if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
                text.pop_back();
            } else if (event->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                SDL_SetClipboardText(text.c_str());
            } else if (event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                text = SDL_GetClipboardText();
            } else if (event->key.keysym.sym == SDLK_RETURN) {
                done = true;
            }
        } else if (event->type == SDL_TEXTINPUT) {
            if (!(SDL_GetModState() & KMOD_CTRL && (event->text.text[0] == 'c' || event->text.text[0] == 'C' || event->text.text[0] == 'v' || event->text.text[0] == 'V'))) {
                if (text.length() < width - 5) {
                    text += event->text.text;
                }
            }
        }
    }
}

void TextInputpad::render() {
    drawBorder(title);
    fillBackColor(40, 90, 80, 255);
    fillForeColor(0, 255, 255, 255);
    for (unsigned int i = 2; i < width - 2; ++i) {
        gfx->setBackColor(30, 70, 55, 255, left + i, top + 2);
        gfx->setForeColor(70, 200, 70, 255, left + i, top + 2);
    }
    gfx->write(text + "_", left + 2, top + 2);
}
