#include "application.hpp"

#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    Application* app = new Application();

    while (app->isRunning()) {
        app->update();

        app->render();

        app->processInput();
    }

    return 0;
}