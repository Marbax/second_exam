#include "Bullet.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Bullet::initBulletShape()
{
    if (!this->texture.loadFromFile(R"(./img/bullet.png)"))
        throw std::system_error(errno, std::system_category(), "Failed to open ./img/bullet.png");
    this->texture.setSmooth(true);
    this->shape.setTexture(&texture);
}

Bullet::Bullet(const unsigned short &posX, const unsigned short &posY, const std::string &direction, const unsigned short range)
{
    try
    {
        initBulletShape();

        if (direction == "left")
            this->dir = left;
        {
            this->bullet_end_pos == posX - range;
        }
        if (direction == "right")
        {
            this->dir = right;
            this->bullet_end_pos == posX + range;
        }
    }
    catch (const std::system_error &ex)
    {
        std::cerr << "Error in Pistol.cpp." << ex.what() << " (" << ex.code() << ")" << std::endl;
    }
}

Bullet::~Bullet()
{
}

const bool &Bullet::getAlive() const { return this->alive; }

void Bullet::updateBullet(const float &dt)
{
    if (this->dir == left && posX <= bullet_end_pos)
        alive = false;
    if (this->dir == right && posX >= bullet_end_pos)
        alive = false;
}

void Bullet::renderBullet(sf::RenderTarget *target) {}
