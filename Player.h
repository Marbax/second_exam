#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
private:
    sf::Sprite spriteTop;
    int top_entityH = 0, top_sprite_posX = 0, top_sprite_posY = 0;
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

    int playerScore, health = 100;
    float CurrentFrame = 0.0f, anim_speed = 0.02f, jumpH = 12.0f, cur_jumpH = 0.0f;
    bool attacking = false;

public:
    // явное отключение конструктора по умолчанию
    Player() = delete;

    Player(float posx, float posY, sf::Image &image, sf::String name);

    // передвижение спрайта(текстуры)
    void setPosition() override;

    // задает координаты спрайта(x , y)
    void setEntitySpriteCoords(int sprite_posX, int sprite_posY,int top_sprite_posX, int top_sprite_posY);

    // задает размер спрайтов(низ_ширина,низ_высота,верх_высота)
    void setEntitySpriteSize(int entity_width, int entity_height, int top_entity_height);

    // движение обьекта(координаты) и смена состояний
    void move(const float boostX, const float boostY, const float &dt) override;

    // попытка реализации "плавных" прыжков ,через падение вверх (НЕ РЕАЛИЗОВАНО)
    void updateJumps(const float &dt);

    // включение атаки (состояние)
    void atack();

    // void control(const float &dt);

    // void checkCollisionWithMap(float tmp_boostX, float tmp_boostY);

    // обновление анимации
    void updateAnimation(const float &dt);

    // обновление компонентов
    void update(const float &dt) override;

    // отрисовка спрайтов
    void render(sf::RenderTarget *target) override;

    //------------------------------------------------------------------------------------------------------------
    //---------------------------------------nice ideas-----------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    /* void Player::updateAnimation(const float &dt)
    {
        if (this->attacking)
        {
            //Set origin depending on direction
            if (this->sprite.getScale().x > 0.f) //Facing left
            {
                this->sprite.setOrigin(96.f, 0.f);
            }
            else //Facing right
            {
                this->sprite.setOrigin(258.f + 96.f, 0.f);
            }

            //Animate and check for animation end
            if (this->animationComponent->play("ATTACK", dt, true))
            {
                this->attacking = false;

                if (this->sprite.getScale().x > 0.f) //Facing left
                {
                    this->sprite.setOrigin(0.f, 0.f);
                }
                else //Facing right
                {
                    this->sprite.setOrigin(258.f, 0.f);
                }
            }
        }
        if (this->movementComponent->getState(IDLE))
        {
            this->animationComponent->play("IDLE", dt);
        }
        else if (this->movementComponent->getState(MOVING_LEFT))
        {
            if (this->sprite.getScale().x < 0.f)
            {
                this->sprite.setOrigin(0.f, 0.f);
                this->sprite.setScale(1.f, 1.f);
            }

            this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        }
        else if (this->movementComponent->getState(MOVING_RIGHT))
        {
            if (this->sprite.getScale().x > 0.f)
            {
                this->sprite.setOrigin(258.f, 0.f);
                this->sprite.setScale(-1.f, 1.f);
            }

            this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
        }
        else if (this->movementComponent->getState(MOVING_UP))
        {
            this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
        }
        else if (this->movementComponent->getState(MOVING_DOWN))
        {
            this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
        }
    } */
};

#endif