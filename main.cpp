#include <stdio.h>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS; // Ennyi ms kell egy frame-hez (1000ms / 60fps = 16.67ms)

Uint32 frameStart;
int frameTime;

using namespace std;

// Gomb strukt�ra
struct Button {
    SDL_FRect rect;
    SDL_Color color;
    SDL_Color hoverColor;
    string text = "asd";
    bool isHovered = false;
    bool isVisible = false;

    Button() {}

    Button(SDL_FRect rect, SDL_Color color, SDL_Color hoverColor) {
        this->rect = rect;
        this->color = color;
        this->hoverColor = hoverColor;
    }
};

Button *karakterinditas, *singlePlayerBT, *easyBt, *mediumBt, *hardBt;
SDL_FPoint *man;
size_t manSize = 0;
bool add, start, singlePlayer;
SDL_FRect kocka;
int dificulty;

// Eg�rpoz�ci� ellen?rz�se pointerrel
bool isMouseOver(Button* button, int mouseX, int mouseY) {
    if (!button) return false;  // V�delem nullptr ellen
    return (mouseX >= button->rect.x && mouseX <= button->rect.x + button->rect.w &&
            mouseY >= button->rect.y && mouseY <= button->rect.y + button->rect.h);
}

void CreateMan(SDL_FPoint point) {
    // N�velj�k a t�mb m�ret�t dinamikusan
    manSize++;

    man = (SDL_FPoint*)realloc(man, manSize * sizeof(SDL_FPoint));

    // �j ember besz�r�sa a t�mb v�g�re
    man[manSize - 1] = point;
    SDL_Log(to_string(man[0].x).c_str());
    SDL_Log(to_string(man[0].y).c_str());
}

void removeFirstMan() {
    if (manSize == 0) return; // Ha nincs mit t�r�lni, kil�p�nk

    // Ha t�bb elem van, akkor el?retoljuk az elemeket
    for (size_t i = 1; i < manSize; i++) {
        man[i - 1] = man[i];
    }

    // Cs�kkentj�k a m�retet
    manSize--;

    // �jram�retezz�k a t�mb�t
    man = (SDL_FPoint*)realloc(man, manSize * sizeof(SDL_FPoint));

    if (manSize == 0) {
        man = NULL; // Ha m�r nincs ember, null�zzuk ki a pointert
    }
}

void render_Button(Button* button) {
    float x, y;
    SDL_GetMouseState(&x, &y);
    if (isMouseOver(button, x, y)) {
        SDL_SetRenderDrawColor(renderer, button->hoverColor.r, button->hoverColor.g, button->hoverColor.b, 255);
    }else {
        SDL_SetRenderDrawColor(renderer, button->color.r, button->color.g, button->color.b, 255);
    }
    SDL_RenderFillRect(renderer, &button->rect);
    button->isVisible = true;
}

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

    karakterinditas = new Button({0, 0, 100, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});
    singlePlayerBT = new Button({350, 100, 100, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});
    easyBt = new Button({350, 100, 200, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});
    mediumBt = new Button({350, 200, 200, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});
    hardBt = new Button({350, 300, 200, 80}, {0, 255, 0, 255}, {0, 0, 0, 255});

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
                SDL_Log("meg van nyomva: inditas");
                if (manSize < 1)
                    add = true;
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

    // return continue to continue
    return SDL_APP_CONTINUE;
}

// This function runs once per frame, and is the heart of the program
SDL_AppResult SDL_AppIterate(void *appstate) {
    frameStart = SDL_GetTicks(); //frame kezd�se

    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    if (singlePlayerBT && !singlePlayer && !start) {
        render_Button(singlePlayerBT);
    }
    if (singlePlayer && !start) {
        render_Button(easyBt);
        render_Button(mediumBt);
        render_Button(hardBt);
    }

    if (start) {
        if (karakterinditas) {
            render_Button(karakterinditas);
        }

        if (add) {
            SDL_FPoint point = {.x = 0, .y = 200};
            CreateMan(point);
            add = false;
        }

        if (manSize == 1) {
            man[0].x++;
            SDL_FRect rect = {.x = man[0].x, .y = man[0].y, .w = 20, .h = 20};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
            if (man[0].x >= 200) {
                removeFirstMan();
            }
        }
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
    free(karakterinditas);
    free(singlePlayerBT);
    free(easyBt);
    free(mediumBt);
    free(hardBt);
    free(man);
}