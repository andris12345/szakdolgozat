#ifndef FELIRAT_H
#define FELIRAT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "../../variables/Variables.h"

class Subtitle {
    std::string text;
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_FRect rect = {};
    TTF_Font* font = nullptr;
    SDL_Color color = {};

    void updateTexture();

public:
    Subtitle();
    Subtitle(TTF_Font* font, SDL_Color color, SDL_FRect rect);
    ~Subtitle();

    void setText(const std::string& newText);
    void render() const;
};
#endif //FELIRAT_H
