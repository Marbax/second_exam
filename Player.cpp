#include "Player.h"

Player::Player(float posX, float posY, sf::Image &image, sf::String name) : Entity(posX, posY, image, name)
{
    playerScore = attacking = 0;
    state = stay_right;
    if (name == "Tarma")
    {
        setEntitySpriteCoords(0, 618, 0, 582);
        setEntitySpriteSize(39, 19, 29);
        sprite.setTextureRect(sf::IntRect(sprite_posX, sprite_posY, entityW, entityH));
        spriteTop.setTexture(texture);
        //spriteTop.setOrigin(entityW/2, top_entityH/2); // установка середины обьекта
        spriteTop.setTextureRect(sf::IntRect(top_sprite_posX, top_sprite_posY, entityW, top_entityH));
    }
}

// задает позицию спрайтов
void Player::setPosition()
{
    if (sitting)
    {
        this->sprite.setPosition(posX, posY);
        this->spriteTop.setPosition(posX, posY - entityH);
        this->sprite.move(0, 6);
        this->spriteTop.move(0, 13);
    }
    else
    {
        this->sprite.setPosition(posX, posY);
        this->spriteTop.setPosition(posX, posY - entityH);
    }
}

// задает координаты спрайта(x , y)
void Player::setEntitySpriteCoords(int sprite_posX, int sprite_posY, int top_sprite_posX, int top_sprite_posY)
{
    this->sprite_posX = sprite_posX;
    this->sprite_posY = sprite_posY;
    this->top_sprite_posX = top_sprite_posX;
    this->top_sprite_posY = top_sprite_posY;
}

// задает размер спрайтов(низ_ширина,низ_высота,верх_высота)
void Player::setEntitySpriteSize(int entity_width, int entity_height, int top_entity_height)
{
    this->entityW = entity_width;
    this->entityH = entity_height;
    this->top_entityH = top_entity_height;
}

void Player::move(const float boostX, const float boostY, const float &dt)
{
    // движение
    if (boostX && !boostY)
    {
        this->isMove = true;
        this->sitting = false;
        if (onGround && life && boostX < 0)
        {
            this->posX += boostX * dt;
            this->state = moving_left;
        }
        if (onGround && life && boostX > 0)
        {
            this->posX += boostX * dt;
            this->state = moving_right;
        }
    }

    // прыжки (может лестницы)
    if (boostY < 0 && onGround)
    {
        this->cur_jumpH = posY - jumpH;
        this->isMove = true;
        this->onGround = false;
        this->sitting = false;
        if (life && state == moving_left)
        {
            this->posX += boostX * dt;
            this->posY += boostY * dt;
            this->state = jump_right;
        }
        if (life && state == moving_right)
        {
            this->posX += boostX * dt;
            this->posY += boostY * dt;
            this->state = jump_left;
        }
        if (life && (state != moving_right || state != moving_left))
        {
            this->posY += boostY * dt;
            this->state = jump_top;
        }
    }

    // приседание (может лестницы)
    if (boostY > 0)
    {
        this->isMove = true;
        if (onGround && life && !sitting && (state == stay_left || state == moving_left || state == down_right))
        {
            this->state = down_left;
            this->posX += boostX / 4 * dt;
        }
        if (onGround && life && !sitting && (state == stay_right || state == moving_right || state == down_left))
        {
            this->state = down_right;
            this->posX += boostX / 4 * dt;
        }
    }
}

void Player::updateJumps(const float &dt)
{

    // падение вниз
    if (!onGround && posY < 170)
    {
        if (state == jump_right)
        {
            this->posY += 0.1f * dt;
            this->posX += 0.1f * dt;
        }
        if (state == jump_left)
        {
            this->posY += 0.1f * dt;
            this->posX -= 0.1f * dt;
        }
        if (state == jump_top)
        {
            this->posY += 0.1f * dt;
        }
    }
    else
    {
        this->cur_jumpH = 0.f;
        this->onGround = true;
        this->isMove = false;
    }
}

void Player::atack()
{
    this->attacking = true;
}
/*
 void control(const float &dt)
    {
        if (sf::Keyboard::isKeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
            {
                // вниз и влево
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
                    move(-0.2f, 0.2f, dt);
                // влево
                else
                    move(-0.2f, 0.f, dt);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
            {
                // вниз и вправо
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
                    move(0.2f, 0.2f, dt);
                // вправо
                else
                    move(0.2f, 0.f, dt);
            }

            // вниз
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
                move(0.f, 0.2f, dt);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
            { // вверх и вправо
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
                    move(1.2f, -1.2f, dt);
                // вверх и влево
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
                    move(-1.2f, -1.2f, dt);
                // вверх
                else
                    move(0.f, -1.2f, dt);
            }

            // атака
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                this->attacking = true;
            }
        }
        else
        {
            // обнуление движения
            this->isMove = false;
        }
    } 
*/
/*
 void checkCollisionWithMap(float tmp_boostX, float tmp_boostY)
    {   
                 // if ((spriteTop.getGlobalBounds()).intersects(sprite.getGlobalBounds())) // колижн детект по мануалу 
                 {
                     //collision
                 }


        for (int i = 0; i < obj.size(); i++)
            if (getRect().intersects(obj[i].rect))
            {
                if (obj[i].name == "solid")
                {
                    if (tmp_boostY > 0)
                    {
                        posY = obj[i].rect.top - entityH;
                        tmp_boostY = 0;
                        onGround = true;
                    }
                    if (tmp_boostY < 0)
                    {
                        posY = obj[i].rect.top + obj[i].rect.height;
                        boostY = 0;
                    }
                    if (tmp_boostX > 0)
                    {
                        posX = obj[i].rect.left - entityW;
                    }
                    if (tmp_boostX < 0)
                    {
                        posX = obj[i].rect.left + obj[i].rect.width;
                    }
                }
                // else { onGround = false; }
            }
    } 
*/
void Player::updateAnimation(const float &dt)
{
    switch (state)
    {
    case moving_right:
    {
        setEntitySpriteCoords(0, 618, 0, 582);
        setEntitySpriteSize(39, 19, 29);
        CurrentFrame += anim_speed * dt;
        if (CurrentFrame > 12)
            CurrentFrame = 0;
        this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + entityW * static_cast<int>(CurrentFrame), top_sprite_posY, entityW, top_entityH));
        this->sprite.setTextureRect(sf::IntRect(sprite_posX + entityW * static_cast<int>(CurrentFrame), sprite_posY, entityW, entityH));
    }
    break;
    case moving_left:
    {
        setEntitySpriteCoords(0, 618, 0, 582);
        setEntitySpriteSize(39, 19, 29);
        CurrentFrame += anim_speed * dt;
        if (CurrentFrame > 12)
            CurrentFrame -= 11;
        this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + entityW * static_cast<int>(CurrentFrame), top_sprite_posY, -entityW, top_entityH));
        this->sprite.setTextureRect(sf::IntRect(sprite_posX + entityW * static_cast<int>(CurrentFrame), sprite_posY, -entityW, entityH));
    }
    break;
    case down_right:
    {
        if (sitting)
        {
            if (CurrentFrame > 4)
                CurrentFrame = 0;

            setEntitySpriteCoords(118, 873, 118, 860);
            setEntitySpriteSize(40, 20, 13);
            CurrentFrame += anim_speed / 7 * dt;
            this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + entityW * static_cast<int>(CurrentFrame), top_sprite_posY, entityW, top_entityH));
            this->sprite.setTextureRect(sf::IntRect(sprite_posX + entityW * static_cast<int>(CurrentFrame), sprite_posY, entityW, entityH));
        }
        else
        {
            if (CurrentFrame > 3)
            {
                CurrentFrame = 0;
                sitting = true;
            }

            setEntitySpriteCoords(1, 868, 1, 848);
            setEntitySpriteSize(38, 20, 20);
            CurrentFrame += anim_speed / 3 * dt;
            this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + entityW * static_cast<int>(CurrentFrame), top_sprite_posY, entityW, top_entityH));
            this->sprite.setTextureRect(sf::IntRect(sprite_posX + entityW * static_cast<int>(CurrentFrame), sprite_posY, entityW, entityH));
        }
    }
    break;
    case stay_right:
    {
        /* CurrentFrame += anim_speed/3 * dt;
            if (CurrentFrame > 22)
                CurrentFrame = 0;
            spriteTop.setTextureRect(sf::IntRect(41 * int(CurrentFrame), 423, 41, 24));
            sprite.setTextureRect(sf::IntRect(41 * int(CurrentFrame), 447, 41, 23)); */

        CurrentFrame += anim_speed/3 * dt;
        if (CurrentFrame > 4)
            CurrentFrame = 0;
        this->spriteTop.setTextureRect(sf::IntRect(39 * int(CurrentFrame), 644, 39, 19));
        this->sprite.setTextureRect(sf::IntRect(39 * int(CurrentFrame), 664, 39, 21));

        /* CurrentFrame += anim_speed / 3 * dt;
        if (CurrentFrame > 18)
            CurrentFrame = 0;
        spriteTop.setTextureRect(sf::IntRect(36 * static_cast<int>(CurrentFrame) + 1, 345, 36, 33));
        sprite.setTextureRect(sf::IntRect(714 + (21 * (static_cast<int>(CurrentFrame) / 4)), 621, 21, 18)); */
    }
    break;
    case stay_left:
    {
        /* CurrentFrame += 0.008 * dt;
            if (CurrentFrame > 22)
                CurrentFrame = 0;
            spriteTop.setTextureRect(IntRect(41 * int(CurrentFrame), 423, -41, 24));
            sprite.setTextureRect(IntRect(41 * int(CurrentFrame), 447, -41, 23)); */

        CurrentFrame += anim_speed / 3 * dt;
        if (CurrentFrame > 4)
            CurrentFrame -= 3;
        this->spriteTop.setTextureRect(sf::IntRect(39 * static_cast<int>(CurrentFrame), 644, -39, 19));
        this->sprite.setTextureRect(sf::IntRect(39 * static_cast<int>(CurrentFrame), 664, -39, 21));

        /* CurrentFrame += 0.005 * dt;
            if (CurrentFrame > 18)
                CurrentFrame = 0;
            spriteTop.setTextureRect(IntRect(36 * int(CurrentFrame) + 1, 345, -36, 33));
            sprite.setTextureRect(IntRect(714 + (21 * int(int(CurrentFrame) / 4)), 621, -21, 18)); */
    }
    break;
    }

    // отключает постоянное передвижение
    /* if (state != down_right || state != down_left)
        {
            if (state == moving_right || state == right)
            {
                state = right;
            }
            if (state == moving_left || state == left)
            {
                state = left;
            }
        }
        if (state == down_right || state == down_left)
        {
        } */

    // анимация стояния после движений и прыжков
    if (!isMove )
    {
        //this->sitting = false;
        if (onGround && life && (state == moving_right || state == stay_right || state == jump_right || state == jump_top))
        {
            this->state = stay_right;
        }
        if (onGround && life && (state == moving_left || state == stay_left || state == jump_left))
        {
            this->state = stay_left;
        }
    }
}

void Player::update(const float &dt)
{
    //control(dt);
    updateJumps(dt);
    updateAnimation(dt);
    setPosition();

    //checkCollisionWithMap(boostX, 0);
    //checkCollisionWithMap(0, boostY);

    // смерть
    /* if (health <= 0)
        {
            life = false;
        } */

    /*         if (!isMove)
        {
            speed = 0;
        }
     */
    /* if (life)
        {
            setPlayerCoordinateForView(posX, posY);
        } */
}

void Player::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
    target->draw(this->spriteTop);
}

//------------------------------------------------------------------------------------------------------------
//---------------------------------------nice ideas-----------------------------------------------------------
//------------------------------------------------------------------------------------------------------------

/*
 void Player::updateAnimation(const float &dt)
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
    } 
*/
