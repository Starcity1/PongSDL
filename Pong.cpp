#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Pong.h"

bool PongApp::onInit() {
    std::cout << "\x1b[33m Attempting to initialize SDL \x1b[0m \n";
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error code: \x1b[31m " << SDL_GetError() << "\x1b[0m.\n";
        return false;
    }
    std::cout << "\x1b[32m SDL succesfully initialized. \x1b[0m \n\n";

    std::cout << "\x1b[33m Attempting to initialize window display \x1b[0m \n";
    _Window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, 0);
    if(_Window == NULL) {
        std::cout << "Error code: \x1b[31m " << SDL_GetError() << "\x1b[0m.\n";
        return false;
    }
    std::cout << "\x1b[32m Window display succesfully initialized. \x1b[0m \n\n";

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    std::cout << "\x1b[33m Attempting to initialize renderer \x1b[0m \n";
    _Renderer = SDL_CreateRenderer(_Window, -1, 0);
    if(_Renderer == NULL) {
        std::cout << "Error code: \x1b[31m " << SDL_GetError() << "\x1b[0m.\n";
        return false;
    }
    std::cout << "\x1b[32m Renderer succesfully initialized. \x1b[0m \n\n";

    std::cout << "\x1b[33m Attempting to initialize png and jpg texstures \x1b[0m \n";
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        std::cout << "Error code: \x1b[31m " << SDL_GetError() << "\x1b[0m.\n";
        return false;
    }
    std::cout << "\x1b[32m PNG and JPG textures succesfully initialized. \x1b[0m \n\n";

    std::cout << "\x1b[33m Attempting to initialize mp3 audio files \x1b[0m\n";
    if (Mix_Init(MIX_INIT_MP3) == 0) {
        std::cout << "Error code: \x1b[31m " << SDL_GetError() << "\x1b[0m.\n";
        return false;
    }

    //Initializing audio mixer.
    // The audio will open these mp3 files with 4800hz as a 16-bit audio.
    // The two represents that it will be a stereo (2 channel) audio.
    // The 2048 represents the chunk size of the audio.
    Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 2048);

    std::cout << "\x1b[32mmp3 audio files succesfully initialized. \x1b[0m \n\n";

    return true;
}

void PongApp::onEvent(SDL_Event* Event) {
    SDL_Scancode sym;
    switch(Event->type) {
    case SDL_QUIT:
        onCleanup();
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        sym = Event->key.keysym.scancode;
        movePlayers(sym);
        break;
    default:
        break;
    }
}

void PongApp::prepareRender() {
    // Creating two rectangles which will become player pads.
    SDL_RenderClear( _Renderer );

    SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 255);

    SDL_Rect p1PlatRect, p2PlatRect;
    p1PlatRect.w = p2PlatRect.w = 25;
    p1PlatRect.h = p2PlatRect.h = 100;

    p1PlatRect.x = sprites[0].x;        //Player 1
    p1PlatRect.y = sprites[0].y;
    
    if(PongBot.withBot) PongBot.MoveBot(sprites[2].y);
    p2PlatRect.x = (PongBot.withBot) ? PongBot.x : sprites[1].x;        //Player 2
    p2PlatRect.y = (PongBot.withBot) ? PongBot.y : sprites[1].y;

    SDL_RenderDrawRect(_Renderer, &p1PlatRect);
    SDL_RenderFillRect(_Renderer, &p1PlatRect);
    
    SDL_RenderDrawRect(_Renderer, &p2PlatRect);
    SDL_RenderFillRect(_Renderer, &p2PlatRect);

    // Creating Ball.
    SDL_Rect ballRect;
    ballRect.w = ballRect.h = 20;
    ballRect.x = sprites[2].x;
    ballRect.y = sprites[2].y;

    SDL_RenderDrawRect(_Renderer, &ballRect);
    SDL_RenderFillRect(_Renderer, &ballRect);

    // After we render the square, we move.
    moveBall();

    SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 255);
}
void PongApp::presentRender() {
    SDL_RenderPresent( _Renderer );
}

void PongApp::onCleanup() {
    //Deallocating window and renderer. And closing SDL in general.
    SDL_DestroyWindow( _Window );
    SDL_DestroyRenderer( _Renderer );

    SDL_Quit();
    system("clear");

    std::cout << "\x1b[32m Closing application...\x1b[0m \n";
}

