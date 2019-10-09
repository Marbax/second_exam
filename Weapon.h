#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <list>
#include "SFML-2.5.1/include/SFML/Graphics.hpp"

class Weapon
{
private:
    std::string name;
    unsigned short dmg;
    unsigned short range;

public:
    Weapon() = delete;
    Weapon(const std::string &name, const unsigned short &dmg, const unsigned short &range);
    virtual ~Weapon() = 0;

    // потом лучше сделать доп абстракцию дальнобойного оружия
    //virtual const std::list<Bullet::Bullet *> &getBulletList() const = 0;

    virtual const std::string &getName() const;
    virtual const unsigned short &getDmg() const;
    virtual const unsigned short &getRange() const;
    virtual bool shootLeft(const unsigned short &posX, const unsigned short &posY, const float &dt) = 0;
    virtual bool shootRight(const unsigned short &posX, const unsigned short &posY, const float &dt) = 0;
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target) = 0;
};

#endif