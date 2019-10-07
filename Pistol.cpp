#include "Pistol.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Pistol::initBulletShape()
{
    if (!this->texture.loadFromFile(R"(./img/bullet.png)"))
        throw std::system_error(errno, std::system_category(), "Failed to open ./img/bullet.png");
    this->texture.setSmooth(true);
    this->shape.setTexture(&texture);
    //this->shape.setOrigin(posX, posY);
}
//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Pistol::Pistol(const unsigned short &dmg, const unsigned short &range) : Weapon("Pistol", dmg, range)
{
    try
    {
        initBulletShape();
    }
    catch (const std::system_error &ex)
    {
        std::cerr << "Error in Bullet.cpp." << ex.what() << " (" << ex.code() << ")" << std::endl;
    }
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
    bullets.push_back(new Bullet(posX, posY, "left", this->getRange(), shape));
}

void Pistol::shootRight(const unsigned short &posX, const unsigned short &posY)
{
    bullets.push_back(new Bullet(posX, posY, "right", this->getRange(), shape));
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

    bullets.remove_if([](Bullet *it) { return !it->getAlive(); });

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
