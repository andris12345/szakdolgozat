#include "Gomb.h"

Gomb::Gomb() {}

Gomb::Gomb(SDL_FRect rect, SDL_Color color, SDL_Color hoverColor) {
    this->rect = rect;
    this->color = color;
    this->hoverColor = hoverColor;
}

bool isMouseOver(Gomb* button, int mouseX, int mouseY) {
    if (!button) return false;
    return (mouseX >= button->rect.x && mouseX <= button->rect.x + button->rect.w &&
            mouseY >= button->rect.y && mouseY <= button->rect.y + button->rect.h);
}

void render_Button(Gomb* button, SDL_Renderer *renderer) {
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