#ifndef PISTOL_H
#define PISTOL_H

#include "Weapon.h"
#include "Bullet.h"
#include <iostream>
#include <list>
#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include "SFML-2.5.1/include/SFML/Audio.hpp"

class Pistol : public Weapon
{
private:
    sf::SoundBuffer sound_buf;
    sf::Sound shoot_sound;
    sf::Texture texture;
    std::list<Bullet *> bullets;
    float atk_speed = 500, cooldown;

public:
    void initBulletTexture();
    void initSounds();

    Pistol(const unsigned short &dmg, const unsigned short &range);
    ~Pistol();
    void shootLeft(const unsigned short &posX, const unsigned short &posY, const float &dt) override;
    void shootRight(const unsigned short &posX, const unsigned short &posY, const float &dt) override;
    //void shootTop(const std::string &direction, const unsigned short &bullet_start_pos);

    void update(const float &dt) override;
    void render(sf::RenderTarget *target) override;
};

#endif