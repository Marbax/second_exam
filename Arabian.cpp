#include "Arabian.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Arabian::initVariables()
{
    //this->state = stay_right;
    //this->onGround = true;
    //this->jumpH = 22.0f;
    //setMaxHealth(100);
    //this->CurrentFrame = 0.0f;
    this->anim_speed = 0.002f;
    //this->jump_speed = 0.3f;
    //this->jumpH = 22.0f;
    //this->cur_jumpH = 0.0f;
    //this->sit_slawer = 0.33f;
    //this->weapon = new Pistol(20, 500);
    this->loop = false;
}

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Arabian::Arabian(const float &posX, const float &posY, sf::Image &image) : Character(posX, posY, image, "Arabian")
{
    initVariables();
}

Arabian::~Arabian()
{
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Arabian::bestAIever(const float &dt)
{
    srand(time(0));
    unsigned short r = rand() % 100;
    
    if (r <= 20)
        move(0.2, 0, dt);
    else if (r >= 21 && r <= 40)
        move(-0.2, 0, dt);
    else if (r >= 41)
        move(0, 0, dt);
}

Pistol &Arabian::getWeapon() { return *this->weapon; }

void Arabian::animate(const bool &right, const unsigned short &frames_count, const float &dt)
{
    CurrentFrame += anim_speed * frames_count * dt;
    if (right)
    {
        if (CurrentFrame > frames_count)
            CurrentFrame = 0;
        frameChange(right);
    }
    else
    {
        if (CurrentFrame > frames_count + 1)
            CurrentFrame = 1;

        frameChange(right);
    }
}

void Arabian::animateLoop(const bool &right, const unsigned short &frames_count, const float &dt)
{
    if (right)
    {
        if (CurrentFrame >= frames_count)
        {
            loop = true;
            CurrentFrame = frames_count;
        }
        else if (CurrentFrame <= 0)
        {
            loop = false;
            CurrentFrame = 0;
        }

        if (loop == false)
            CurrentFrame += anim_speed * frames_count * dt;

        if (loop == true)
            CurrentFrame -= anim_speed * frames_count * dt;

        frameChange(right);
    }
    else
    {
        if (CurrentFrame >= frames_count + 1)
        {
            loop = true;
            CurrentFrame = frames_count + 1;
        }
        else if (CurrentFrame <= 1)
        {
            loop = false;
            CurrentFrame = 1;
        }

        if (loop == false)
            CurrentFrame += anim_speed * frames_count * dt;

        if (loop == true)
            CurrentFrame -= anim_speed * frames_count * dt;

        frameChange(right);
    }
}

void Arabian::movingAnimation(const bool &right, const float &dt)
{
    unsigned short frames_count = 12;
    setSpriteCoords(7, 204);
    setSpriteSize(624 / frames_count, 52);
    animate(right, frames_count, dt);
}

void Arabian::idleAnimation(const bool &right, const float &dt)
{
    unsigned short frames_count = 6;
    setSpriteCoords(6, 24);
    setSpriteSize(240 / frames_count, 48);
    animateLoop(right, frames_count, dt);
}

void Arabian::updateAnimation(const float &dt)
{
    switch (state)
    {
    case moving_right:
    {
        movingAnimation(false, dt);
    }
    break;
    case moving_left:
    {
        movingAnimation(true, dt);
    }
    break;
    case down_right:
    {
    }
    break;
    case down_left:
    {
    }
    break;
    case stay_right:
    {
        idleAnimation(false, dt);
    }
    break;
    case stay_left:
    {
        idleAnimation(true, dt);
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

void Arabian::update(const float &dt)
{
    bestAIever(dt);
    updateJumps(dt);
    updateAnimation(dt);
    setPosition();
    if (weapon)
        this->weapon->update(dt);
}

void Arabian::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);

    if (weapon)
        this->weapon->render(target);
}
