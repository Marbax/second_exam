#include "Bullet.h"

Bullet::Bullet(const unsigned short &posX, const unsigned short &posY, const std::string &direction,
               const unsigned short range, sf::Texture &texture) : posX(posX), posY(posY)
{

    this->sprite.setTexture(texture);
    this->sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);

    if (direction == "left")
    {
        this->sprite.rotate(180);
        this->dir = left;
        this->bullet_end_pos = posX - range;
    }
    else if (direction == "right")
    {
        this->dir = right;
        this->bullet_end_pos = posX + range;
    }
}

Bullet::~Bullet()
{
}


//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

const sf::Vector2f &Bullet::getBulletPosition() const { return this->sprite.getPosition(); }

void Bullet::setAlive(const bool &alive) { this->alive = alive; }

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
    {
        this->posX -= boostX * dt;
        this->sprite.setPosition(posX, posY);
    }
    else if (this->dir == right)
    {
        this->posX += boostX * dt;
        this->sprite.setPosition(posX, posY);
    }
}

void Bullet::update(const float &dt)
{
    checkAlive();
    if (alive)
    {
        updateBullet(dt);
    }
}

void Bullet::render(sf::RenderTarget *target)
{
    if (alive)
        target->draw(this->sprite);
}
