#include "Bullet.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------
/* 
void Bullet::initBulletShape()
{
    if (!this->texture.loadFromFile(R"(./img/bullet.png)"))
        throw std::system_error(errno, std::system_category(), "Failed to open ./img/bullet.png");
    this->texture.setSmooth(true);
    this->shape.setTexture(&texture);
    this->shape.setOrigin(posX, posY);
}
 */
Bullet::Bullet(const unsigned short &posX, const unsigned short &posY, const std::string &direction, const unsigned short range, sf::RectangleShape &shape) : posX(posX), posY(posY)
{
    try
    {
        //initBulletShape();
        shape.setOrigin(posX, posY);

        if (direction == "left")
        {
            this->dir = left;
            this->bullet_end_pos = posX - range;
        }
        else if (direction == "right")
        {
            this->dir = right;
            this->bullet_end_pos = posX + range;
        }
    }
    catch (const std::system_error &ex)
    {
        std::cerr << "Error in Bullet.cpp." << ex.what() << " (" << ex.code() << ")" << std::endl;
    }
}

Bullet::~Bullet()
{
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

const bool &Bullet::getAlive() const { return this->alive; }

void Bullet::checkAlive()
{
    if (this->dir == left && posX <= bullet_end_pos)
        alive = false;
    else if (this->dir == right && posX >= bullet_end_pos)
        alive = false;
}

void Bullet::updateBullet(const float &dt)
{
    if (this->dir == left)
        this->shape.setPosition(posX - boostX, posY);
    else if (this->dir == right)
        this->shape.setPosition(posX + boostX, posY);
}

void Bullet::update(const float &dt)
{
    if (alive)
    {
        checkAlive();

        updateBullet(dt);
    }
}

void Bullet::render(sf::RenderTarget *target)
{
    if (alive)
        target->draw(this->shape);
}
