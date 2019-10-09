#ifndef ENTITY_H
#define ENTITY_H
#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include "SFML-2.5.1/include/SFML/Window.hpp"
#include "SFML-2.5.1/include/SFML/System.hpp"
#include <iostream>

//------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------БАЗОВЫЙ_КЛАСС_ОБЬЕКТА-------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

class Entity
{
private:
protected:
    float posX = 0.0f, posY = 0.0f;                                 // текущая позиция обьекта
    int spriteW = 0, spriteH = 0, sprite_posX = 0, sprite_posY = 0; // высота,ширина, координаты спрайта по x, по y
    bool life = 1, isMove = 0, onGround = 0, sitting = 0;           // доп состояния
    sf::Texture texture;
    sf::Sprite sprite;
    sf::String name = "NONE";

public:
    // явное отключение конструктора по умолчанию
    Entity() = delete;
    Entity(const float &posX, const float &posY, sf::Image &image, sf::String name);
    virtual ~Entity();

    virtual void setPosX(const float &posX);
    virtual void setPosY(const float &posY);
    virtual const float &getPosX() const;
    virtual const float &getPosY() const;
    virtual void setMove(const bool &isMove);
    //virtual void move(const float &boostX, const float &boostY, const float &dt) = 0;
    virtual void update(const float &dt) = 0;
    virtual void setPosition() = 0;
    virtual void render(sf::RenderTarget *target) = 0;
};

#endif