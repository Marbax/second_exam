#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Pistol.h"

class Character : public Entity
{
private:
    int health;

    void initVariables();

protected:
    float CurrentFrame, anim_speed, jump_speed, jumpH, cur_jumpH, sit_slawer;
    Pistol *weapon = nullptr;
    enum state
    {
        stay_left,
        moving_left,
        stay_right,
        moving_right,
        down_left,
        down_right,
        jump_top,
        jump_left,
        jump_right

    } state;

public:
    Character() = delete;

    Character(const float &posX, const float &posY, sf::Image &image, const sf::String &name);

    virtual ~Character() = 0;

    virtual Pistol &getWeapon();

    virtual void setOnGround(const bool &b);

    virtual const bool &isOnGround() const;

    // передвижение спрайта(текстуры)
    void setPosition() override;

    // задает координаты спрайта(x , y)
    virtual void setSpriteCoords(const int &sprite_posX, const int &sprite_posY);

    // задает размер спрайтов(низ_ширина,низ_высота)
    virtual void setSpriteSize(const int &sprite_width, const int &sprite_height);

    // движение обьекта(координаты) и смена состояний
    virtual void move(const float &boostX, const float &boostY, const float &dt);

    // кое-какие прыжки
    virtual void updateJumps(const float &dt);

    // включение атаки
    virtual void atack(const float &dt);

    // void control(const float &dt);

    // обновление анимации
    virtual void updateAnimation(const float &dt) = 0;

    // обновление компонентов
    void update(const float &dt) override;

    // отрисовка спрайтов
    void render(sf::RenderTarget *target) override;
};

#endif