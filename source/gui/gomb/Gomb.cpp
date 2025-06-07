#include "Gomb.h"

#include <ostream>
#include <utility>


Gomb::Gomb() = default;

Gomb::Gomb(SDL_FRect rect, SDL_Color color, SDL_Color hoverColor, std::string text, TTF_Font* font) {
    this->rect = rect;
    this->color = color;
    this->hoverColor = hoverColor;
    this->text = std::move(text);
    this->subtitle = new Subtitle(font, {0, 0, 0}, {rect.x, rect.y, 0, 0});
    subtitle->setText(this->text);
}

Gomb::~Gomb() {
    delete subtitle;
}

bool isMouseOver(Gomb* button, float mouseX, float mouseY) {
    if (!button) return false;
    return (mouseX >= button->getRect().x && mouseX <= button->getRect().x + button->getRect().w &&
            mouseY >= button->getRect().y && mouseY <= button->getRect().y + button->getRect().h);
}

void render_Button(Gomb* button) {
    float x, y;
    SDL_GetMouseState(&x, &y);

    if (isMouseOver(button, x, y)) {
        SDL_SetRenderDrawColor(renderer, button->getHoverColor().r, button->getHoverColor().g, button->getHoverColor().b, 255);
    }else {
        SDL_SetRenderDrawColor(renderer, button->getColor().r, button->getColor().g, button->getColor().b, 255);
    }
    SDL_RenderFillRect(renderer, &button->getRect());
    button->setIsVisible(true);

    button->getSubtitle()->render();
}

void Gomb::setRect(SDL_FRect rect) { this->rect = rect; }

void Gomb::setColor(SDL_Color color) { this->color = color; }

void Gomb::setHoverColor(SDL_Color hoverColor) { this->hoverColor = hoverColor; }

void Gomb::setText(std::string text) { this->text = std::move(text); }

void Gomb::setIsHovered(bool isHovered) { this->isHovered = isHovered; }

void Gomb::setIsVisible(bool isVisible) { this->isVisible = isVisible; }

void Gomb::setSubtitleText() { this->subtitle->setText(this->getText()); }

SDL_FRect& Gomb::getRect() { return rect; }

SDL_Color Gomb::getColor() { return color; }

SDL_Color Gomb::getHoverColor() { return hoverColor; }

std::string Gomb::getText() { return text; }

bool Gomb::getIsHovered() const { return isHovered; }

bool Gomb::getIsVisible() const { return isVisible; }

Subtitle *Gomb::getSubtitle() { return subtitle; }
