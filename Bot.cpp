#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Bot.h"

void Bot::InitBot(int initX, int initY, bool useBot) {
    this->x = initX, this->y = initY;
    this->withBot = useBot;
}

void Bot::MoveBot(int ballY) {
    // sprites[1].y = (sprites[1].y > 0) ? sprites[1].y - 20 : 0;
    this->y = (this->y > 0) ? ballY - 50 : 0;
    this->y = (this->y < 380) ? ballY - 50 : 380;
}

void Bot::PlayerLoses() {
    std::cout << "\x1b[31m Player One could not handle the powerful PongBot! \x1b[32m"
    << "Pong Bot wins!\x1b[0m\n";
}