#include <stdio.h>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>

#include "Variables.h"
#include "CreateMan.h"
#include "MoveMan.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS; // Ennyi ms kell egy frame-hez (1000ms / 60fps = 16.67ms)

SDL_AppResult SDL_AppInit(void **appstate, int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == false){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't initialize SDL!", SDL_GetError(), NULL);
        return SDL_APP_FAILURE;
    }

    // 800x450 is 16:9
    if (SDL_CreateWindowAndRenderer("hello SDL3", 800, 450, 0, &window, &renderer) == false){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't create window/renderer!", SDL_GetError(), NULL);
        return SDL_APP_FAILURE;
    }

    kocka.h = kocka.w = 20;

    karakterinditas = new Gomb({0, 0, 100, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});
    singlePlayerBT = new Gomb({350, 100, 100, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});
    easyBt = new Gomb({350, 100, 200, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});
    mediumBt = new Gomb({350, 200, 200, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});
    hardBt = new Gomb({350, 300, 200, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});

    // return success!
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
            if (karakterinditas->isVisible && isMouseOver(karakterinditas, x, y)) {
                SDL_FPoint point = {.x = 0, .y = 200};
                CreateManToPool(point);
            }
            if (singlePlayerBT->isVisible && isMouseOver(singlePlayerBT, x, y)) {
                SDL_Log("meg van nyomva: singlePlayerBT");
                singlePlayer = true;
                singlePlayerBT->isVisible = false;
            }
            if (easyBt->isVisible && isMouseOver(easyBt, x, y)) {
                SDL_Log("meg van nyomva: easyBT");
                dificulty = 0.5;
                start = true;
                easyBt->isVisible = false;
                mediumBt->isVisible = false;
                hardBt->isVisible = false;
            }
            if (mediumBt->isVisible && isMouseOver(mediumBt, x, y)) {
                SDL_Log("meg van nyomva: mediumBT");
                dificulty = 1;
                start = true;
                easyBt->isVisible = false;
                mediumBt->isVisible = false;
                hardBt->isVisible = false;
            }
            if (hardBt->isVisible && isMouseOver(hardBt, x, y)) {
                SDL_Log("meg van nyomva: hardBT");
                dificulty = 1.5;
                start = true;
                easyBt->isVisible = false;
                mediumBt->isVisible = false;
                hardBt->isVisible = false;
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
    delete karakterinditas;
    delete singlePlayerBT;
    delete easyBt;
    delete mediumBt;
    delete hardBt;

    free(window);
    free(renderer);
    free(man);
    free(pool);
}