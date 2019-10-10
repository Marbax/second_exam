#include "Character.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Character::initVariables()
{
    this->state = stay_right;
    this->onGround = true;
    this->jumpH = 22.0f;
    this->health = 100;
    this->CurrentFrame = 0.0f;
    this->anim_speed = 0.02f;
    this->jump_speed = 0.3f;
    this->jumpH = 22.0f;
    this->cur_jumpH = 0.0f;
    this->sit_slawer = 0.33f;
    //this->weapon = new Pistol(20, 500);
}

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Character::Character(const float &posX, const float &posY, sf::Image &image, const sf::String &name) : Entity(posX, posY, image, name)
{
    initVariables();
}

Character::~Character()
{
    if (weapon)
    {
        delete weapon;
    }
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

// задает позицию спрайтов
void Character::setPosition()
{
    this->sprite.setPosition(posX, posY);
}

void Character::setMaxHealth(const unsigned short &max_hp) { this->health = max_hp; }

void Character::damage(const unsigned short &dmg)
{
    if (this->health < 0)
        this->life = false;
    this->health -= dmg;
}

Pistol &Character::getWeapon() { return *this->weapon; }

void Character::setOnGround(const bool &b) { this->onGround = b; }

const bool &Character::isOnGround() const { return this->onGround; }

// задает координаты спрайта(x , y)
void Character::setSpriteCoords(const int &sprite_posX, const int &sprite_posY)
{
    this->sprite_posX = sprite_posX;
    this->sprite_posY = sprite_posY;
}

// задает размер спрайтов(низ_ширина,низ_высота,верх_высота)
void Character::setSpriteSize(const int &sprite_width, const int &sprite_height)
{
    this->spriteW = sprite_width;
    this->spriteH = sprite_height;
}

void Character::move(const float &boostX, const float &boostY, const float &dt)
{
    // движение
    if (boostX && !boostY)
    {
        this->isMove = true;
        this->sitting = false;
        if (this->onGround && this->life && boostX < 0)
        {
            this->posX += boostX * dt;
            this->state = moving_left;
        }
        if (this->onGround && this->life && boostX > 0)
        {
            this->posX += boostX * dt;
            this->state = moving_right;
        }
    }

    // прыжки (может лестницы)
    if (boostY < 0 && this->onGround && !this->sitting)
    {
        this->cur_jumpH = this->jumpH;
        this->isMove = true;
        this->onGround = false;
        this->sitting = false;
        if (this->life && this->state == moving_left)
        {
            this->state = jump_left;
        }
        else if (this->life && this->state == moving_right)
        {
            this->state = jump_right;
        }
        else if (this->life && (this->state != moving_right || this->state != moving_left))
        {
            this->state = jump_top;
        }
    }

    // приседание (может лестницы)
    if (boostY > 0)
    {
        this->isMove = true;
        if (onGround && life && !sitting && (state == stay_left || state == moving_left))
        {
            this->state = down_left;
            this->posX += boostX * dt * sit_slawer;
        }
        else if (onGround && life && !sitting && (state == stay_right || state == moving_right))
        {
            this->state = down_right;
            this->posX += boostX * dt * sit_slawer;
        }
    }
}

void Character::updateJumps(const float &dt)
{

    if (!onGround)
    {
        // падение вверх
        if (cur_jumpH > 0)
        {
            if (state == jump_left)
            {
                this->posX -= jump_speed * dt;
                this->posY -= jump_speed * dt;
            }
            else if (state == jump_right)
            {
                this->posX += jump_speed * dt;
                this->posY -= jump_speed * dt;
            }
            else if (state == jump_top)
            {
                this->posY -= jump_speed * dt;
            }
            this->cur_jumpH -= jump_speed * dt;
        }
        // падение вниз
        if (cur_jumpH <= 0)
        {
            if (state == jump_left)
            {
                this->posX -= jump_speed * dt;
                this->posY += jump_speed * dt;
            }
            else if (state == jump_right)
            {
                this->posX += jump_speed * dt;
                this->posY += jump_speed * dt;
            }
            else if (state == jump_top)
            {
                this->posY += jump_speed * dt;
            }
        }
    }
    else
    {
        this->cur_jumpH = 0.f;
        this->onGround = true;
        this->isMove = false;
    }
}

void Character::atack(const float &dt)
{
    if (this->state == stay_left || this->state == moving_left || this->state == down_left || this->state == jump_left)
        weapon->shootLeft(this->sprite.getGlobalBounds().left, this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height * 0.25, dt);
    else if (this->state == stay_right || this->state == moving_right || this->state == down_right || this->state == jump_right)
        weapon->shootRight(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height * 0.25, dt);
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

void Character::movingAnimation(const bool &right, const unsigned short &frame_limit)
{
}

void Character::frameChange(const bool &right)
{
    if (right)
        this->sprite.setTextureRect(sf::IntRect(sprite_posX + spriteW * static_cast<int>(CurrentFrame), sprite_posY, spriteW, spriteH));

    else
        this->sprite.setTextureRect(sf::IntRect(sprite_posX + spriteW * static_cast<int>(CurrentFrame), sprite_posY, -spriteW, spriteH));
}
/* 
void Character::updateAnimation(const float &dt)
{
    switch (state)
    {
    case moving_right:
    {
        setSpriteCoords(0, 618);
        setSpriteSize(39, 19);
        CurrentFrame += anim_speed * dt;
        if (CurrentFrame > 12)
            CurrentFrame = 0;
        frameChange(true);
    }
    break;
    case moving_left:
    {
        setSpriteCoords(0, 618);
        setSpriteSize(39, 19);
        CurrentFrame += anim_speed * dt;
        if (CurrentFrame > 13)
            CurrentFrame = 1;
        frameChange(false);
    }
    break;
    case down_right:
    {
        if (sitting)
        {
            if (CurrentFrame > 4)
                CurrentFrame = 0;

            setSpriteCoords(0, 618);
            setSpriteSize(39, 19);
            CurrentFrame += anim_speed * dt * 0.22f;
            frameChange(true);
        }
        else
        {
            if (CurrentFrame > 3)
            {
                CurrentFrame = 0;
                sitting = true;
            }

            setSpriteCoords(0, 618);
            setSpriteSize(39, 19);
            CurrentFrame += anim_speed * dt * 0.33f;
            frameChange(true);
        }
    }
    break;
    case down_left:
    {
        if (sitting)
        {
            if (CurrentFrame > 5)
                CurrentFrame = 1;

            setSpriteCoords(0, 618);
            setSpriteSize(39, 19);
            CurrentFrame += anim_speed * dt * 0.22f;
            frameChange(false);
        }
        else
        {
            if (CurrentFrame > 4)
            {
                CurrentFrame = 1;
                sitting = true;
            }

            setSpriteCoords(0, 618);
            setSpriteSize(39, 19);
            CurrentFrame += anim_speed * dt * 0.33f;
            frameChange(false);
        }
    }
    break;
    case stay_right:
    {
        setSpriteCoords(0, 618);
        setSpriteSize(39, 19);
        CurrentFrame += anim_speed * dt * 0.33f;
        if (CurrentFrame > 4)
            CurrentFrame = 0;
        frameChange(true);
    }
    break;
    case stay_left:
    {
        setSpriteCoords(0, 618);
        setSpriteSize(39, 19);
        CurrentFrame += anim_speed * dt * 0.33f;
        if (CurrentFrame > 5)
            CurrentFrame = 1;
        frameChange(false);
    }
    break;
    }

    // анимация стояния после движений и прыжков
    if (!isMove && !sitting)
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
 */
void Character::update(const float &dt)
{

    //control(dt);
    updateJumps(dt);
    updateAnimation(dt);
    setPosition();
    if (weapon)
        this->weapon->update(dt);
}

void Character::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);

    if (weapon)
        this->weapon->render(target);
}
