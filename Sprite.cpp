#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Pong.h"

void PongApp::movePlayers(SDL_Scancode sym) {
    // int p1OldY = sprites[0].y;
    // int p2OldY = sprites[1].y;

    switch(sym) {
    case SDL_SCANCODE_Q:
        if(xDirection > 1 && PongBot.withBot)
        if(xDirection < 0) PlayerOneLoses();
        PlayerTwoLoses();
        break;
    case SDL_SCANCODE_W:
        sprites[0].y = (sprites[0].y > 0) ? sprites[0].y - 20 : 0;
        break;
    case SDL_SCANCODE_S:
        sprites[0].y = (sprites[0].y < 380) ? sprites[0].y + 20 : 380;
        break;
    case SDL_SCANCODE_UP:
        if(PongBot.withBot) break;
        sprites[1].y = (sprites[1].y > 0) ? sprites[1].y - 20 : 0;
        break;
    case SDL_SCANCODE_DOWN:
        if(PongBot.withBot) break;
        sprites[1].y = (sprites[1].y < 380) ? sprites[1].y + 20 : 380;
        break;
    default:
        break;
    }

    //Code to check the position for the players and ball.

    // if(p1OldY != sprites[0].y) {
    //     std::cout << "New \x1b[33m" << sprites[0].spriteName 
    //     << "\x1b[0m position :: \x1b[32m" << sprites[0].y << "\x1b[0m \n";
    // } else if(p2OldY != sprites[1].y) {
    //     std::cout << "New \x1b[33m" << sprites[1].spriteName 
    //     << "\x1b[0m position :: \x1b[32m" << sprites[1].y << "\x1b[0m \n";
    // }
}

void PongApp::moveBall() {
    // int oldX = sprites[2].x, oldY = sprites[2].y;

    // Beautiful chunk of if-else statements that determine collision.
    if(sprites[2].y < 0 || sprites[2].y > 460) {
        Mix_PlayMusic(SFX[0], 0);
        yDirection *= -1;
    }
    // If it collides horizontally, then one of the two players looses.
    if(sprites[2].x < 0 || sprites[2].x > 700) {
        if(xDirection < 0 && PongBot.withBot) BotWins();
        if(xDirection < 0) PlayerOneLoses();
        PlayerTwoLoses();
    }

    // Detecting collision from the players.
    if((sprites[2].x < 100 && sprites[2].x > 75) && (sprites[2].y > sprites[0].y && sprites[2].y < sprites[0].y + 100)) {
        Mix_PlayMusic(SFX[0], 0);
        sprites[2].x = 100;
        xDirection *= -1;
    }

    if(PongBot.withBot) {
        if((sprites[2].x > 595 && sprites[2].x < 620) && (sprites[2].y > PongBot.y && sprites[2].y < PongBot.y + 100)) {
            Mix_PlayMusic(SFX[0], 0);
            sprites[2].x = 595;
            xDirection *= -1;
        }
    } else if((sprites[2].x > 595 && sprites[2].x < 620) && (sprites[2].y > sprites[1].y && sprites[2].y < sprites[1].y + 100)) {
        Mix_PlayMusic(SFX[0], 0);
        sprites[2].x = 595;
        xDirection *= -1;
    }

    sprites[2].y += (yDirection * 2);
    sprites[2].x += (xDirection * 2);

    // std::cout << "yDirection :: \x1b[33m" << yDirection << "\x1b[0m \n";

    // if(oldX != sprites[2].x || oldY != sprites[2].y) {
    //     std::cout << "New \x1b[33m" << sprites[2].spriteName 
    //     << "\x1b[0m position :: \x1b[32m" 
    //     << sprites[2].x << ", " << sprites[2].y<< "\x1b[0m \n";
    // }
}