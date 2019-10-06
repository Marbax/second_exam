#include "Pistol.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Pistol::Pistol(const unsigned short &dmg, const unsigned short &range) : Weapon("Pistol", dmg, range)
{
}

Pistol::~Pistol()
{

    while (bullets.size())
    {
        delete bullets.back();
        bullets.pop_back();
    }
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Pistol::shootLeft(const unsigned short &posX, const unsigned short &posY)
{
    bullets.push_back(new Bullet(posX, posY, "left", this->getRange()));
}

void Pistol::shootRight(const unsigned short &posX, const unsigned short &posY)
{
    bullets.push_back(new Bullet(posX, posY, "right", this->getRange()));
}

void Pistol::update(const float &dt)
{

    for (auto it : bullets)
    {
        if (!it->getAlive())
        {
            delete it;
        }
    }

    bullets.remove_if([](Bullet it) { return !it.getAlive(); });

    /* 
    for (size_t i = 0; i < bullets.size(); i++)
    {
        if (!bullets[i]->getAlive())
        {
            delete bullets.at(i);
            bullets.
        }
    } */
}
