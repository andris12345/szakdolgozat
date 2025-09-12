#include "Felirat.h"

Subtitle::Subtitle() = default;

Subtitle::Subtitle(TTF_Font* _font, SDL_Color _color, SDL_FRect _rect): font(_font), color(_color), rect(_rect) {}

Subtitle::~Subtitle() {
    if (texture) SDL_DestroyTexture(texture);
    if (surface) SDL_DestroySurface(surface);
}

void Subtitle::setText(const std::string& newText) {
    if (newText == text) return;
    text = newText;
    updateTexture();
}

void Subtitle::setRect(SDL_FRect newRect) {
    rect = newRect;
}

void Subtitle::updateTexture() {
    if (texture) SDL_DestroyTexture(texture);
    if (surface) SDL_DestroySurface(surface);

    surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
    if (!surface) {
        SDL_Log("asdTTF_RenderText_Solid failed: %s", SDL_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        return;
    }

    rect.w = surface->w;
    rect.h = surface->h;

}

void Subtitle::render() const {
    if (texture) {
        SDL_RenderTexture(renderer, texture, nullptr, &rect);
    }
}