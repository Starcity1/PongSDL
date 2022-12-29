#include <iostream>
#include <SDL2/SDL.h>
#include "Pong.h"

void PongApp::PlayerOneLoses() {
    onCleanup();
    std::cout << "\x1b[31m Player One was defeated!"
    << "\x1b[32m Player Two takes the crown!.\x1b[0m\n";
    exit(0);
}
void PongApp::PlayerTwoLoses() {
    onCleanup();
    std::cout << "\x1b[31m Player Two was defeated!"
    << "\x1b[32m Player One takes the crown!.\x1b[0m\n";
    exit(0);
}

void PongApp::BotWins() {
    onCleanup();
    PongBot.PlayerLoses();
    exit(0);
}