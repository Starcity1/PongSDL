#include <iostream>
#include <string>
#include <stdio.h>
#include "Pong.h"
#include "Bot.h"

int PongApp::onExecute(bool withBot = false) {

    if(!onInit()) {
        std::cout << "\x1b[31m Error: Program not Initialized.\x1b[0m \n";
        return -1;
    }

    // Creating and adding sprites.
    SDL_Event Event;
    Sprite p1Plat(75, 190, "PlayerOne");
    sprites.push_back(p1Plat);

    Sprite p2Plat(620, 190, "PlayerTwo");
    sprites.push_back(p2Plat);
    if(withBot) {PongBot.InitBot(620, 190, withBot); std::cout << "Using bot\n";}

    Sprite ball(360, 240, "Ball");
    sprites.push_back(ball);

    // Creating and importing SFX.
    Mix_Music* bounce;
    bounce = Mix_LoadMUS("Assets/SFX/bounce.mp3");
    if(bounce == NULL) {
        std::cout << "\x1b[31m Error: Could not load mp3 audio.\n"
        << "Error code: " << SDL_GetError() << "\x1b[0m\n";
        return -2;
    }
    SFX.push_back(bounce);

    while(isRunning) {
        while(SDL_PollEvent(&Event)) {
            onEvent(&Event);
        }

        prepareRender();
        presentRender();

        SDL_Delay(16);
    }
    onCleanup();
    return 0;
}

int main(int argc, char** argv) {
    PongApp app;

    if(argc > 1 && std::string(argv[1]) == "-bot") {
        std::cout << "\x1b[32m Initializing and using bot.\x1b[0m\n";
        app.onExecute(true);
        return 0;
    }

    app.onExecute();

    return 0;
}