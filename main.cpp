#include <iostream>
#include <ostream>
#include <cstdio>
#include <string>
#include <filesystem>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>

#include "source/variables/Variables.h"
#include "source/unit/create/CreateMan.h"
#include "source/unit/fighter/Fighter.h"
#include "source/unit/move/MoveMan.h"
#include "source/unit/ranged/Ranged.h"
#include "source/unit/tank/Tank.h"

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

const int FRAME_DELAY = 1000 / TARGET_FPS; // Ennyi ms kell egy frame-hez (1000ms / 60fps = 16.67ms)

SDL_AppResult SDL_AppInit(void **appstate, int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) == false){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't initialize SDL!", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << SDL_GetError() << std::endl;
    }
    font = TTF_OpenFont("../../assets/albert-text/AlbertText-Bold.ttf", fontSize);
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << SDL_GetError() << std::endl;
    }
    namespace fs = std::filesystem;
    std::string filePath = "D:/CLion/szakdolgozat/assets/albert-text/AlbertText-Bold.ttf";

    if (fs::exists(filePath)) {

        std::cout << "A file letezik!" << std::endl;
    } else {
        std::cout << "A file nem letezik." << std::endl;
    }

    // 800x450 is 16:9
    if (SDL_CreateWindowAndRenderer("hello SDL3", width, height, 0, &window, &renderer) == false){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't create window/renderer!", SDL_GetError(), nullptr);
        return SDL_APP_FAILURE;
    }

    kocka.h = kocka.w = 20;

    return SDL_APP_CONTINUE;
}


// This function runs when a new event occurs
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_EVENT_QUIT:
            // end the program, reporting success to the OS
                return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            if (event->key.key == SDLK_ESCAPE)
            {
                // end the program on ESC key,
                // returning success to the OS
                return SDL_APP_SUCCESS;
            }
        case SDL_EVENT_MOUSE_BUTTON_DOWN :{
            float x, y;
            SDL_GetMouseState(&x, &y);
            if (singlePlayerBT->getIsVisible() && isMouseOver(singlePlayerBT, x, y)) {
                SDL_Log("meg van nyomva: singlePlayerBT");
                singlePlayer = true;
                singlePlayerBT->setIsVisible(false);
            }
            if (easyBt->getIsVisible() && isMouseOver(easyBt, x, y)) {
                SDL_Log("meg van nyomva: easyBT");
                dificulty = 0.5;
                start = true;
                easyBt->setIsVisible(false);
                mediumBt->setIsVisible(false);
                hardBt->setIsVisible(false);
            }
            if (mediumBt->getIsVisible() && isMouseOver(mediumBt, x, y)) {
                SDL_Log("meg van nyomva: mediumBT");
                dificulty = 1;
                start = true;
                easyBt->setIsVisible(false);
                mediumBt->setIsVisible(false);
                hardBt->setIsVisible(false);
            }
            if (hardBt->getIsVisible() && isMouseOver(hardBt, x, y)) {
                SDL_Log("meg van nyomva: hardBT");
                dificulty = 1.5;
                start = true;
                easyBt->setIsVisible(false);
                mediumBt->setIsVisible(false);
                hardBt->setIsVisible(false);
            }
            if (fighterBt->getIsVisible() && isMouseOver(fighterBt, x, y)) {
                Fighter fighter = Fighter(0);
                CreateManToPool(fighter);
            }
            if (rangedBt->getIsVisible() && isMouseOver(rangedBt, x, y)) {
                Ranged ranged = Ranged(1);
                CreateManToPool(ranged);
            }
            if (tankBt->getIsVisible() && isMouseOver(tankBt, x, y)) {
                Tank tank = Tank(2);
                CreateManToPool(tank);
            }
        }
        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    frameStart = SDL_GetTicks();

    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    if (singlePlayerBT && !singlePlayer && !start) {
        render_Button(singlePlayerBT, renderer);
    }
    if (singlePlayer && !start) {
        render_Button(easyBt, renderer);
        render_Button(mediumBt, renderer);
        render_Button(hardBt, renderer);
    }

    if (start) {
       Move(renderer);
    }

    SDL_RenderPresent(renderer);

    //fix fps
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY) {
        SDL_Delay(FRAME_DELAY - frameTime);
    }

    return SDL_APP_CONTINUE;
}

// This function runs once at shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    delete fighterBt;
    delete rangedBt;
    delete tankBt;
    delete singlePlayerBT;
    delete easyBt;
    delete mediumBt;
    delete hardBt;

    TTF_CloseFont(font);

    free(window);
    free(renderer);
    free(man);
    free(pool);
}