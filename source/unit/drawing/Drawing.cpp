#include "Drawing.h"

void hpKirajzolasHelper() {
    if (player1.getManSize() != 0) {
        if (player1.getManAt(0)->getHp() != player1.getManAt(0)->getMaxHp()) {
            hpkirajzolas(renderer, *player1.getManAt(0));
        }
    }else if (player1.getPoolSize() != 0) {
        if (player1.getPoolAt(0)->getHp() != player1.getPoolAt(0)->getMaxHp()) {
            hpkirajzolas(renderer, *player1.getPoolAt(0));
        }
    }
    if (player2.getManSize() != 0 ) {
        if (player2.getManAt(0)->getHp() != player2.getManAt(0)->getMaxHp()) {
            hpkirajzolas(renderer, *player2.getManAt(0));
        }
    }else if (player2.getPoolSize() != 0) {
        if (player2.getPoolAt(0)->getHp() != player2.getPoolAt(0)->getMaxHp()) {
            hpkirajzolas(renderer, *player2.getPoolAt(0));
        }
    }
}

void hpkirajzolas(SDL_Renderer *renderer, GameUnit &man) {
    float ratio = static_cast<float>(man.getHp()) / static_cast<float>(man.getMaxHp());
    float hpwidth = ratio * emberszelesseg;
    SDL_FRect rect = {.x = man.getRect().x, .y = (man.getRect().y - 15), .w = emberszelesseg, .h = 5};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect = {.x = man.getRect().x, .y = (man.getRect().y - 15), .w = hpwidth, .h = 5};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void kirajzolas(SDL_Renderer *renderer, GameUnit &man) {
    SDL_FRect rect = {.x = man.getRect().x, .y = man.getRect().y, .w = emberszelesseg, .h = emberszelesseg};
    SDL_SetRenderDrawColor(renderer, man.getColor().r, man.getColor().g, man.getColor().b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void unitKirajzolas(SDL_Renderer *renderer) {
    if (player1.getPoolSize() > 0) {
        for (int i = 0; i < player1.getPoolSize(); i++) {
            kirajzolas(renderer, *player1.getPoolAt(i));
        }
    }
    if (player2.getPoolSize() > 0) {
        for (int i = 0; i < player2.getPoolSize(); i++) {
            kirajzolas(renderer, *player2.getPoolAt(i));
        }
    }
    if (player1.getManSize() > 0) {
        for (int i = 0; i < player1.getManSize(); i++) {
            kirajzolas(renderer, *player1.getManAt(i));
        }
    }
    if (player2.getManSize() > 0) {
        for (int i = 0; i < player2.getManSize(); i++) {
            kirajzolas(renderer, *player2.getManAt(i));
        }
    }
}

void basekirajzolas(SDL_Renderer *renderer) {
    SDL_FRect rect = {.x = 20, .y = (emberKezdoY - 100), .w = behuzasi_tavolsag - 40, .h = emberKezdoY - 100 + emberszelesseg};
    SDL_SetRenderDrawColor(renderer, 137, 81, 41, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect = {.x = (behuzasi_tavolsag + mezoszam * mezoszelesseg + 20), .y = (emberKezdoY - 100), .w = behuzasi_tavolsag - 40, .h = emberKezdoY - 100 + emberszelesseg};
    SDL_RenderFillRect(renderer, &rect);

    float ratio = static_cast<float>(player1.getBaseHp()) / static_cast<float>(maxBaseHp); // sajat
    float hpwidth = ratio * (behuzasi_tavolsag - 40);
    rect = {.x = 20, .y = (emberKezdoY - 100 - 15), .w = behuzasi_tavolsag - 40, .h = 5};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect = {.x = 20, .y = (emberKezdoY - 100 - 15), .w = hpwidth, .h = 5};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    ratio = static_cast<float>(player2.getBaseHp()) / static_cast<float>(maxEnemybaseHp);  //enemy
    hpwidth = ratio * (behuzasi_tavolsag - 40);
    rect = {.x = behuzasi_tavolsag + mezoszam * mezoszelesseg + 20, .y = (emberKezdoY - 100 - 15), .w = behuzasi_tavolsag - 40, .h = 5};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect = {.x = behuzasi_tavolsag + mezoszam * mezoszelesseg + 20, .y = (emberKezdoY - 100 - 15), .w = hpwidth, .h = 5};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void toronyKirajzolas(SDL_Renderer *renderer) {
    for (int i = 0; i < 2; i++) {
        if (player1.getTowerAt(i)->isExists()) {
            renderTower(renderer, *player1.getTowerAt(i));
        }else {
            if (buyTower) {
                render_Button(tower1Bt);
                render_Button(tower2Bt);
            }else {
                tower1Bt->setIsVisible(false);
                tower2Bt->setIsVisible(false);
            }

            if (deleteBt->getIsVisible()) {
                render_Button(deleteBt);
            }

            if (!player1.getTowerAt(0)->isExists()) {
                render_Button(tower1Holder);
            }else {
                tower1Holder->setIsVisible(false);
            }
            if (!player1.getTowerAt(1)->isExists()) {
                render_Button(tower2Holder);
            }else {
                tower2Holder->setIsVisible(false);
            }
        }
        if (player2.getTowerAt(i)->isExists()) {
            renderTower(renderer, *player2.getTowerAt(i));
        }
    }
}