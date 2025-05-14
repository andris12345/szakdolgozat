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
    return (mouseX >= button->getRect().x && mouseX <= button->getRect().x + button->getRect().w &&
            mouseY >= button->getRect().y && mouseY <= button->getRect().y + button->getRect().h);
}

void render_Button(Gomb* button, SDL_Renderer *renderer) {
    float x, y;
    SDL_GetMouseState(&x, &y);

    if (isMouseOver(button, x, y)) {
        SDL_SetRenderDrawColor(renderer, button->getHoverColor().r, button->getHoverColor().g, button->getHoverColor().b, 255);
    }else {
        SDL_SetRenderDrawColor(renderer, button->getColor().r, button->getColor().g, button->getColor().b, 255);
    }
    SDL_RenderFillRect(renderer, &button->getRect());
    button->setIsVisible(true);

    SDL_Surface* surface = TTF_RenderText_Solid(font, button->getText().c_str(), button->getText().length(), fontColor);
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
    SDL_RenderTexture(renderer, texture, nullptr, &button->getRect());

    SDL_DestroyTexture(texture); // texture szabadítása
}

void Gomb::setRect(SDL_FRect rect) {
    this->rect = rect;
}

void Gomb::setColor(SDL_Color color) {
    this->color = color;
}

void Gomb::setHoverColor(SDL_Color hoverColor) {
    this->hoverColor = hoverColor;
}

void Gomb::setText(std::string text) {
    this->text = std::move(text);
}

void Gomb::setIsHovered(bool isHovered) {
    this->isHovered = isHovered;
}

void Gomb::setIsVisible(bool isVisible) {
    this->isVisible = isVisible;
}

SDL_FRect& Gomb::getRect() {
    return rect;
}

SDL_Color Gomb::getColor() {
    return color;
}

SDL_Color Gomb::getHoverColor() {
    return hoverColor;
}

std::string Gomb::getText() {
    return text;
}

bool Gomb::getIsHovered() const {
    return isHovered;
}

bool Gomb::getIsVisible() const {
    return isVisible;
}