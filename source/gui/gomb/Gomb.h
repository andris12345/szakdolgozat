#ifndef GOMB_H
#define GOMB_H

#include <SDL3/SDL.h>
#include <string>
#include "../../variables/Variables.h"

class Gomb{
    SDL_FRect rect = {};
    SDL_Color color = {};
    SDL_Color hoverColor = {};
    std::string text;
    bool isHovered = false;
    bool isVisible = false;
    Subtitle *subtitle = nullptr;
public:
    Gomb();

    Gomb(SDL_FRect rect, SDL_Color color, SDL_Color hoverColor, std::string text, TTF_Font* font);

    ~Gomb();

    void setRect(SDL_FRect rect);
    void setColor(SDL_Color color);
    void setHoverColor(SDL_Color hoverColor);
    void setText(std::string text);
    void setIsHovered(bool isHovered);
    void setIsVisible(bool isVisible);
    void setSubtitleText();

    SDL_FRect& getRect();
    SDL_Color getColor();
    SDL_Color getHoverColor();
    std::string getText();
    bool getIsHovered() const;
    bool getIsVisible() const;
    Subtitle* getSubtitle();
};

bool isMouseOver(Gomb* button, float mouseX, float mouseY);

void render_Button(Gomb* button);
#endif //GOMB_H
