#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include "SFML-2.5.1/include/SFML/Graphics.hpp"

class Bullet
{
private:
    sf::Texture texture;
    sf::RectangleShape shape;
    float boostX = 0.3f, boostY = 0.0f;
    float posX = 0.0f, posY = 0.0f;
    bool alive = true;

    unsigned short bullet_start_pos;
    unsigned short bullet_end_pos;
    enum dir
    {
        left,
        right
    } dir;

public:
    void initBulletShape();

    Bullet(const unsigned short &posX, const unsigned short &posY, const std::string &direction, const unsigned short range);

    ~Bullet();

    const bool &getAlive() const;
    void updateBullet(const float &dt);
    void renderBullet(sf::RenderTarget *target);
};

#endif BULLET_H