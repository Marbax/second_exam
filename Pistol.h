#ifndef PISTOL_H
#define PISTOL_H

#include "Weapon.h"
#include "Bullet.h"
#include <iostream>
#include <list>
#include <set>
#include "SFML-2.5.1/include/SFML/Graphics.hpp"

class Pistol : public Weapon
{
private:
    //std::vector<Bullet *> bullets;
    std::list<Bullet *> bullets;
    //unsigned short atk_speed;

public:
    Pistol(const unsigned short &dmg, const unsigned short &range);
    ~Pistol();
    void shootLeft(const unsigned short &posX, const unsigned short &posY);
    void shootRight(const unsigned short &posX, const unsigned short &posY);
    //void shootTop(const std::string &direction, const unsigned short &bullet_start_pos);

    void update(const float &dt);
};

#endif PISTOL_H