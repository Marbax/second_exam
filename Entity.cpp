#include "Entity.h"

Entity::Entity(float posX, float posY, sf::Image &image, sf::String name) : posX(posX), posY(posY), name(name)
{
    texture.loadFromImage(image);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<int>(entityW / 2), static_cast<int>(entityH / 2)); // установка середины обьекта как точки его начала ,а не верхнего левого угла
}

float Entity::getPosX() const { return this->posX; }
float Entity::getPosY() const { return this->posY; }

void Entity::setMove(bool isMove)
{
    this->isMove = isMove;
}
