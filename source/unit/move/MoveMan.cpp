#include "MoveMan.h"

#include <format>

void Move(SDL_Renderer *renderer) {
    //mező jelölő vonalak
    for (int i = 0; i <= mezoszam; i++) {
        SDL_FRect rect = {.x = (mezoszelesseg * i) + behuzasi_tavolsag , .y = 200-emberszelesseg/2, .w = 1, .h = emberszelesseg + emberszelesseg/2};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    if (fighterBt) {
        render_Button(fighterBt);
    }
    if (rangedBt) {
        render_Button(rangedBt); // todo atvinni a mainbe a buttonrendereket
    }
    if (tankBt) {
        render_Button(tankBt);
    }

    basekirajzolas(renderer);

    //poolban lévő emberek kirajzolása + kitevése a mapra
    if (!player1.getPoolIsEmpty()) {
        if (map[0] == 0) {
            player1.getPoolAt(0)->setRectX(player1.getPoolAt(0)->getRextX() + 1);
            if (player1.getPoolAt(0)->getRextX() + emberszelesseg/2 >= behuzasi_tavolsag) {
                map[0] = 1;
                CreateManToMap(false);
            }
        }
        for (int i = 0; i < player1.getPoolSize(); i++) {
            if (!player1.getPoolIsEmpty() && map[0] == 2 && (player1.getPoolAt(i)->getRange() == 3 || i == 0)) {
                if (frameSzamlalo == 0) {
                    attackFromPool(*player1.getPoolAt(i), false);
                }
            }
            if (player1.getPoolSize() > 0) {
                kirajzolas(renderer, *player1.getPoolAt(i));
            }
        }
    }

    //enemy pool kirajzolasa
    if (!player2.getPoolIsEmpty()) {
        if (map[mezoszam - 1] == 0) {
            player2.getPoolAt(0)->setRectX(player2.getPoolAt(0)->getRextX() - 1);
            if (player2.getPoolAt(0)->getRextX() + emberszelesseg/2 <= behuzasi_tavolsag + mezoszam * mezoszelesseg) {
                map[mezoszam - 1] = 2;
                CreateManToMap(true);
            }
        }
        for (int i = 0; i < player2.getPoolSize(); i++) {
            if (!player2.getPoolIsEmpty() && map[mezoszam - 1] == 1 && (player2.getPoolAt(i)->getRange() == 3 || i == 0)) {
                if (frameSzamlalo == 0) {
                    attackFromPool(*player2.getPoolAt(i), true);
                }
            }
            if (player2.getPoolSize() > 0) {
                kirajzolas(renderer, *player2.getPoolAt(i));
            }
        }
    }
    //kirajzolás + léptetés az embereknek
    if (player1.getManSize() > 0) {
        for (int i = player1.getManSize() - 1; i >= 0; i--) {
            mozgatas(*player1.getManAt(i));
            kirajzolas(renderer, *player1.getManAt(i));
        }
    }

    //enemy kirajzolasa + leptetese
    if (player2.getManSize() > 0) {
        for (int i = 0; i < player2.getManSize(); i++) {
            mozgatas(*player2.getManAt(i));
            kirajzolas(renderer, *player2.getManAt(i));
        }
    }

    hpKirajzolasHelper();
}

void mozgatas(GameUnit &man){
    if (man.getIsEnemy()) {
        if ((man.getRect().x + emberszelesseg / 2) > (mezoszam - 1) * mezoszelesseg + behuzasi_tavolsag + mezoszelesseg / 2) {
            man.setRectX(man.getRextX() - 1);
        }else {
            int hely = ((man.getRextX() + emberszelesseg/2) - behuzasi_tavolsag) / mezoszelesseg;

            if (hely == 0) {
                if ((man.getRect().x + emberszelesseg / 2) > behuzasi_tavolsag + mezoszelesseg / 2) {
                    man.setRectX(man.getRextX() - 1);
                }
            }else if (map[hely - 1] == 0 || man.getRextX() > (hely * mezoszelesseg + behuzasi_tavolsag + (mezoszelesseg - emberszelesseg) / 2)) {
                man.setRectX(man.getRextX() - 1);
            }
            if (man.getRextX() + (emberszelesseg/2) == ((hely) * mezoszelesseg) + behuzasi_tavolsag - 1) {
                map[hely] = 0;
                map[hely - 1] = 2;
                man.setPos(hely - 1);
            }
            if (frameSzamlalo == 0) {
                attackHandler(man, hely);
                tower_attack.TowerAttackHandler();
            }
        }
    }else {
        if ((man.getRect().x + emberszelesseg / 2) < behuzasi_tavolsag) {
            man.setRectX(man.getRextX() + 1);
        }else {
            int hely = ((man.getRextX() + emberszelesseg/2) - behuzasi_tavolsag) / mezoszelesseg;

            if (hely == mezoszam-1) {
                if (man.getRextX() < (hely * mezoszelesseg + behuzasi_tavolsag + (mezoszelesseg - emberszelesseg) / 2)) {
                    man.setRectX(man.getRextX() + 1);
                }
            }else if (map[hely + 1] == 0 || man.getRextX() < (hely * mezoszelesseg + behuzasi_tavolsag + (mezoszelesseg - emberszelesseg) / 2)) {
                man.setRectX(man.getRextX() + 1);
            }
            if (man.getRextX() + (emberszelesseg/2) == ((hely + 1) * mezoszelesseg) + behuzasi_tavolsag) {
                map[hely] = 0;
                map[hely + 1] = 1;
                man.setPos(hely + 1);
            }
            if (frameSzamlalo == 0) {
                attackHandler(man, hely);
                tower_attack.TowerAttackHandler();
            }
        }
    }
}

void levelUp(bool isenemy) {
    if (isenemy) {
        player2.setLevel(player2.getLevel() + 1);

        fighterBt->getSubtitle()->setText("Fighter: " + std::format("{:.1f}",(10 + 10 * player2.getLevel() * 0.25)));
        rangedBt->getSubtitle()->setText("Ranged: " + std::format("{:.1f}",(15 + 15 * player2.getLevel() * 0.25)));
        tankBt->getSubtitle()->setText("Tank: " +  std::format("{:.1f}",(20 + 20 * player2.getLevel() * 0.25)));


        tower1Bt->getSubtitle()->setText("Tower 1 " + std::format("{:.1f}",(10 + 10 * player2.getLevel() * 0.25)));
        tower2Bt->getSubtitle()->setText("Tower 2 " + std::format("{:.1f}",(10 + 10 * player2.getLevel() * 0.25)));
    }else {
        player1.setLevel(player1.getLevel() + 1);

        fighterBt->getSubtitle()->setText("Fighter: " + std::format("{:.1f}",(10 + 10 * player1.getLevel() * 0.25)));
        rangedBt->getSubtitle()->setText("Ranged: " + std::format("{:.1f}",(15 + 15 * player1.getLevel() * 0.25)));
        tankBt->getSubtitle()->setText("Tank: " +  std::format("{:.1f}",(20 + 20 * player1.getLevel() * 0.25)));


        tower1Bt->getSubtitle()->setText("Tower 1 " + std::format("{:.1f}",(10 + 10 * player1.getLevel() * 0.25)));
        tower2Bt->getSubtitle()->setText("Tower 2 " + std::format("{:.1f}",(10 + 10 * player1.getLevel() * 0.25)));
    }
}