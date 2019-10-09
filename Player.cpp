#include "Player.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Player::initVariables()
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
    this->score = 0;
    this->weapon = new Pistol(20, 500);
}

void Player::initSprite()
{
    setSpriteCoords(0, 618);
    setSpriteSize(39, 19);
    this->sprite.setTextureRect(sf::IntRect(sprite_posX, sprite_posY, spriteW, spriteH));
    sprite.setOrigin(spriteW / 2, 0);
}

void Player::initTopSprite()
{
    setTopSpriteCoords(0, 582);
    setTopSpriteSize(39, 29);
    spriteTop.setTexture(texture);
    spriteTop.setOrigin(top_spriteW / 2, top_spriteH);
    spriteTop.setTextureRect(sf::IntRect(top_sprite_posX, top_sprite_posY, top_spriteW, top_spriteH));
}

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Player::Player(const float &posX, const float &posY, sf::Image &image, sf::String name) : Character(posX, posY, image, name)
{
    initVariables();
    initSprite();
    initTopSprite();
}

Player::~Player() {}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

sf::FloatRect Player::getRect()
{
    //sf::FloatRect tmp = sprite.getGlobalBounds();
    //tmp.height += spriteTop.getGlobalBounds().height;

    // если присесть и прыгнуть можно провалиться (это фича xD)
    sf::FloatRect tmp = this->spriteTop.getGlobalBounds();
    tmp.height += (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height) - (this->spriteTop.getGlobalBounds().top + this->spriteTop.getGlobalBounds().height);
    return tmp;
}

// задает позицию спрайтов
void Player::setPosition()
{

    if (sitting)
    {
        this->sprite.setPosition(posX, posY);
        this->spriteTop.setPosition(posX, posY);
        this->sprite.move(0.f, 12.f);
        this->spriteTop.move(0.f, 20.f);
    }
    else if (state == stay_left || state == stay_right)
    {
        this->sprite.setPosition(posX, posY);
        this->spriteTop.setPosition(posX, posY);
        this->sprite.move(0.f, 2.f);
        this->spriteTop.move(0.f, 12.f);
    }
    else
    {
        this->sprite.setPosition(posX, posY);
        this->spriteTop.setPosition(posX, posY);
        this->spriteTop.move(0.f, 10.f);
    }
}

// задает координаты спрайта(x , y)
void Player::setTopSpriteCoords(const int &top_sprite_posX, const int &top_sprite_posY)
{
    this->top_sprite_posX = top_sprite_posX;
    this->top_sprite_posY = top_sprite_posY;
}

// задает размер спрайтов(низ_ширина,низ_высота,верх_высота)
void Player::setTopSpriteSize(const int &top_sprite_width, const int &top_sprite_height)
{
    this->top_spriteW = top_sprite_width;
    this->top_spriteH = top_sprite_height;
}

void Player::atack(const float &dt)
{
    if (this->state == stay_left || this->state == moving_left || this->state == down_left || this->state == jump_left)
        weapon->shootLeft(this->spriteTop.getGlobalBounds().left, this->spriteTop.getGlobalBounds().top + this->spriteTop.getGlobalBounds().height * 0.75f, dt);
    else if (this->state == stay_right || this->state == moving_right || this->state == down_right || this->state == jump_right)
        weapon->shootRight(this->spriteTop.getGlobalBounds().left + this->spriteTop.getGlobalBounds().width, this->spriteTop.getGlobalBounds().top + this->spriteTop.getGlobalBounds().height * 0.75f, dt);
}

void Player::topFrameChange(const bool &right)
{
    if (right)
        this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + spriteW * static_cast<int>(CurrentFrame), top_sprite_posY, spriteW, top_spriteH));
    else
        this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + spriteW * static_cast<int>(CurrentFrame), top_sprite_posY, -spriteW, top_spriteH));
}

void Player::updateAnimation(const float &dt)
{
    switch (state)
    {
    case moving_right:
    {
        setSpriteCoords(0, 618);
        setSpriteSize(39, 19);
        setTopSpriteCoords(0, 582);
        setTopSpriteSize(39, 29);
        CurrentFrame += anim_speed * dt;
        if (CurrentFrame > 12)
            CurrentFrame = 0;
        frameChange(true);
        topFrameChange(true);
    }
    break;
    case moving_left:
    {
        setSpriteCoords(0, 618);
        setSpriteSize(39, 19);
        setTopSpriteCoords(0, 582);
        setTopSpriteSize(39, 29);
        CurrentFrame += anim_speed * dt;
        if (CurrentFrame > 13)
            CurrentFrame = 1;
        frameChange(false);
        topFrameChange(false);
    }
    break;
    case down_right:
    {
        if (sitting)
        {
            if (CurrentFrame > 4)
                CurrentFrame = 0;

            setSpriteCoords(119, 880);
            setSpriteSize(41, 7);
            setTopSpriteCoords(119, 860);
            setTopSpriteSize(41, 20);
            CurrentFrame += anim_speed * dt * 0.22f;
            frameChange(true);
            topFrameChange(true);
        }
        else
        {
            if (CurrentFrame > 3)
            {
                CurrentFrame = 0;
                sitting = true;
            }

            setSpriteCoords(1, 868);
            setSpriteSize(38, 20);
            setTopSpriteCoords(1, 848);
            setTopSpriteSize(38, 20);
            CurrentFrame += anim_speed * dt * 0.33f;
            frameChange(true);
            topFrameChange(true);
        }
    }
    break;
    case down_left:
    {
        if (sitting)
        {
            if (CurrentFrame > 5)
                CurrentFrame = 1;

            setSpriteCoords(119, 880);
            setSpriteSize(41, 7);
            setTopSpriteCoords(119, 860);
            setTopSpriteSize(41, 20);
            CurrentFrame += anim_speed * dt * 0.22f;
            frameChange(false);
            topFrameChange(false);
        }
        else
        {
            if (CurrentFrame > 4)
            {
                CurrentFrame = 1;
                sitting = true;
            }

            setSpriteCoords(1, 868);
            setSpriteSize(38, 20);
            setTopSpriteCoords(1, 848);
            setTopSpriteSize(38, 20);
            CurrentFrame += anim_speed * dt * 0.33f;
            frameChange(false);
            topFrameChange(false);
        }
    }
    break;
    case stay_right:
    {
        setSpriteCoords(1, 664);
        setSpriteSize(38, 17);
        setTopSpriteCoords(1, 644);
        setTopSpriteSize(38, 19);
        CurrentFrame += anim_speed * dt * 0.33f;
        if (CurrentFrame > 4)
            CurrentFrame = 0;
        frameChange(true);
        topFrameChange(true);
    }
    break;
    case stay_left:
    {
        setSpriteCoords(1, 664);
        setSpriteSize(38, 17);
        setTopSpriteCoords(1, 644);
        setTopSpriteSize(38, 19);
        CurrentFrame += anim_speed * dt * 0.33f;
        if (CurrentFrame > 5)
            CurrentFrame = 1;
        frameChange(false);
        topFrameChange(false);
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

void Player::update(const float &dt)
{
    /* 
    for (const auto it : weapon->getBulletList())
    {
        std::cout << it->getBulletPosition().x << " " << it->getBulletPosition().y << std::endl;
    }
 */
    //control(dt);
    updateJumps(dt);
    updateAnimation(dt);
    setPosition();
    this->weapon->update(dt);
}

void Player::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
    target->draw(this->spriteTop);
    this->weapon->render(target);
}
