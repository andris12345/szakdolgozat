#ifndef GOMB_H
#define GOMB_H

#include <SDL3/SDL.h>
#include <string>

struct Gomb{
    SDL_FRect rect;
    SDL_Color color;
    SDL_Color hoverColor;
    std::string text = "asd";
    bool isHovered = false;
    bool isVisible = false;

    Gomb();

    Gomb(SDL_FRect rect, SDL_Color color, SDL_Color hoverColor);
};

bool isMouseOver(Gomb* button, int mouseX, int mouseY);

void render_Button(Gomb* button, SDL_Renderer *renderer);
#endif //GOMB_H
