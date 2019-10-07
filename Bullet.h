#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include "SFML-2.5.1/include/SFML/Graphics.hpp"

class Bullet
{
private:
    sf::Sprite sprite;                  //bullet sprite
    float boostX = 0.7f, boostY = 0.0f; //bullet speed
    float posX = 0.0f, posY = 0.0f;     //bullet pos
    bool alive = true;                  //bullet exists/not

    unsigned short bullet_end_pos;
    enum dir
    {
        left,
        right
    } dir;

public:
    Bullet(const unsigned short &posX, const unsigned short &posY, const std::string &direction,
           const unsigned short range, sf::Texture &texture);

    ~Bullet();

    const sf::Vector2f &getBulletPosition() const;
    void setAlive(const bool &alive);
    const bool &getAlive() const;
    void checkAlive();
    void updateBullet(const float &dt);
    void update(const float &dt);
    void render(sf::RenderTarget *target);
};

#endif