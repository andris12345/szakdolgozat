#include "Gomb.h"

#include <iostream>
#include <ostream>
#include <utility>


Gomb::Gomb() = default;

Gomb::Gomb(SDL_FRect rect, SDL_Color color, SDL_Color hoverColor, std::string text) {
    this->rect = rect;
    this->color = color;
    this->hoverColor = hoverColor;
    this->text = std::move(text);
}

bool isMouseOver(Gomb* button, float mouseX, float mouseY) {
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

    SDL_Surface* surface = TTF_RenderText_Solid(font, button->text.c_str(), button->text.length(), fontColor);
    if (surface == nullptr) {
        // Hibaellenőrzés
        std::cerr << "Error creating text surface: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (texture == nullptr) {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return;
    }

    // Szöveg renderelése
    SDL_RenderTexture(renderer, texture, nullptr, &button->rect); // SDL_RenderCopy helyett

    SDL_DestroyTexture(texture); // texture szabadítása
}