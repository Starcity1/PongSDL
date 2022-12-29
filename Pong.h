#ifndef PONG_H
#define PONG_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "Bot.h"

/*
How this pong application will work::

Compile code:
g++ -std=c++20 -o exec -Wall -Wextra -fsanitize=address -lSDL2 -lSDL2_image -lSDL2_mixer *.cpp 
Execute code:
./exec [-bot]

-bot: Flag that enables AI to play against. Disables player 2 movements.

Gameplay - Regular pong game, If a player misses the ball
or quits, the other player wins.

Controls :
    W -         (Player 1) Move up.
    D -         (Player 1) Move down.

    UP_KEY -    (Player 2) Move up.
    DOWN_KEY -  (Player 2) Move down.

    Q -     Quit game.

Winner is displayed on the console.
*/

// Sprite structure, this will include the ball, the pads and the scores.
struct Sprite {
    int x;
    int y;
    std::string spriteName;
    SDL_Texture* texture;
    Sprite(int inX, int inY, std::string inName, SDL_Texture* inTexture = nullptr)
    : x(inX), y(inY), spriteName(inName), texture(inTexture) {}
};

class PongApp {
private:

    // Vector contains all platforms, it has format:
    //[Player 1, Player 2, Ball, Net, Numbers from 0 to 10]
    std::vector<Sprite> sprites;

    // Vector contails all sfx for pong, it has format:
    //[bounce.mp3]
    std::vector<Mix_Music*> SFX;

    // *Note: For future projects, it may be better to use unordered maps.

    // Bot
    Bot PongBot;

    // Used for ball movement.
    int yDirection = -1, xDirection = -1;

    bool isRunning;
    SDL_Window* _Window;
    SDL_Renderer* _Renderer;

// Member functions to initialize application.
public:
    PongApp() : isRunning(true) {}
    bool onInit();

// Member functions that oversee the application
public:
    int onExecute(bool withBot);
    
    void onEvent(SDL_Event* Event);
    void movePlayers(SDL_Scancode sym);
    void moveBall();

    //Gameplay wise.
    void PlayerOneLoses();
    void PlayerTwoLoses();
    void BotWins();

    void prepareRender();
    void presentRender();

    void onCleanup();

};

#endif //PONG_H