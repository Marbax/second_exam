#include "Entity.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Entity::Entity(const float &posX, const float &posY, sf::Image &image, sf::String name) : posX(posX), posY(posY), name(name)
{
    texture.loadFromImage(image);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<int>(spriteW / 2), static_cast<int>(spriteH / 2)); // установка середины обьекта как точки его начала ,а не верхнего левого угла
}

Entity::~Entity() {}
//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

sf::FloatRect Entity::getSpriteRect() { return this->sprite.getGlobalBounds(); }

void Entity::setPosX(const float &posX) { this->posX = posX; }
void Entity::setPosY(const float &posY) { this->posY = posY; }
const float &Entity::getPosX() const { return this->posX; }
const float &Entity::getPosY() const { return this->posY; }

void Entity::setMove(const bool &isMove)
{
    this->isMove = isMove;
}
