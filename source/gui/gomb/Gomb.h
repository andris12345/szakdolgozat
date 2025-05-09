#ifndef GOMB_H
#define GOMB_H

#include <SDL3/SDL.h>
#include <string>
#include "../../variables/Variables.h"

struct Gomb{
    SDL_FRect rect = {};
    SDL_Color color = {};
    SDL_Color hoverColor = {};
    std::string text;
    bool isHovered = false;
    bool isVisible = false;

    Gomb();

    Gomb(SDL_FRect rect, SDL_Color color, SDL_Color hoverColor, std::string text);
};

bool isMouseOver(Gomb* button, float mouseX, float mouseY);

void render_Button(Gomb* button, SDL_Renderer *renderer);
#endif //GOMB_H
