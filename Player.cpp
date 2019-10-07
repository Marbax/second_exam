#include "Player.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Player::Player(float posX, float posY, sf::Image &image, sf::String name) : Entity(posX, posY, image, name)
{
    playerScore = attacking = 0;
    state = stay_right;
    onGround = true;
    if (name == "Tarma")
    {
        this->weapon = new Pistol(20, 500);
        setEntitySpriteCoords(0, 618, 0, 582);
        setEntitySpriteSize(39, 19, 29);
        sprite.setTextureRect(sf::IntRect(sprite_posX, sprite_posY, entityW, entityH));
        spriteTop.setTexture(texture);
        //spriteTop.setOrigin(entityW/2, top_entityH/2); // установка середины обьекта
        spriteTop.setTextureRect(sf::IntRect(top_sprite_posX, top_sprite_posY, entityW, top_entityH));
    }
}

Player::~Player()
{
    delete weapon;
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Player::setOnGround(bool b) { this->onGround = b; }

bool Player::isOnGround() const { return onGround; }

sf::FloatRect Player::getRect()
{
    //sf::FloatRect tmp = sprite.getGlobalBounds();
    //tmp.height += spriteTop.getGlobalBounds().height;

    // если присесть и прыгнуть можно провалиться (это фича xD)
    sf::FloatRect tmp = spriteTop.getGlobalBounds();
    tmp.height += (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) - (spriteTop.getGlobalBounds().top + spriteTop.getGlobalBounds().height);
    return tmp;
}

// задает позицию спрайтов
void Player::setPosition()
{

    if (sitting)
    {
        this->sprite.setPosition(posX, posY);
        this->spriteTop.setPosition(posX, posY - entityH);
        this->sprite.move(0, 10);
        this->spriteTop.move(0, -2);
    }
    else if (state == stay_left || state == stay_right)
    {
        this->sprite.setPosition(posX, posY);
        this->spriteTop.setPosition(posX, posY - entityH);
        this->spriteTop.move(0, -2);
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
        this->cur_jumpH = jumpH;
        this->isMove = true;
        this->onGround = false;
        this->sitting = false;
        if (life && state == moving_left)
        {
            this->state = jump_right;
        }
        else if (life && state == moving_right)
        {
            this->state = jump_left;
        }
        else if (life && (state != moving_right || state != moving_left))
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
            this->posX += boostX * dt * 0.33f;
        }
        else if (onGround && life && !sitting && (state == stay_right || state == moving_right))
        {
            this->state = down_right;
            this->posX += boostX * dt * 0.33f;
        }
    }
}

void Player::updateJumps(const float &dt)
{

    if (!onGround)
    {
        // падение вверх
        if (cur_jumpH > 0)
        {
            if (state == jump_right)
            {
                this->posX -= jump_speed * dt;
                this->posY -= jump_speed * dt;
            }
            else if (state == jump_left)
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
            if (state == jump_right)
            {
                this->posX -= jump_speed * dt;
                this->posY += jump_speed * dt;
            }
            else if (state == jump_left)
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

void Player::atack(const float &dt)
{
    if (this->state == stay_left || this->state == moving_left || this->state == down_left || this->state == jump_left)
        weapon->shootLeft(this->spriteTop.getGlobalBounds().left, this->spriteTop.getGlobalBounds().top + this->spriteTop.getGlobalBounds().height / 2, dt);
    else if (this->state == stay_right || this->state == moving_right || this->state == down_right || this->state == jump_right)
        weapon->shootRight(this->spriteTop.getGlobalBounds().left, this->spriteTop.getGlobalBounds().top + this->spriteTop.getGlobalBounds().height / 2, dt);

    //this->attacking = true;
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
        if (CurrentFrame > 13)
            CurrentFrame = 1;
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

            setEntitySpriteCoords(119, 880, 119, 860);
            setEntitySpriteSize(41, 7, 20);
            CurrentFrame += anim_speed * dt * 0.22f;
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
            CurrentFrame += anim_speed * dt * 0.33f;
            this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + entityW * static_cast<int>(CurrentFrame), top_sprite_posY, entityW, top_entityH));
            this->sprite.setTextureRect(sf::IntRect(sprite_posX + entityW * static_cast<int>(CurrentFrame), sprite_posY, entityW, entityH));
        }
    }
    break;
    case down_left:
    {
        if (sitting)
        {
            if (CurrentFrame > 5)
                CurrentFrame = 1;

            setEntitySpriteCoords(119, 880, 119, 860);
            setEntitySpriteSize(40, 7, 20);
            CurrentFrame += anim_speed * dt * 0.22f;
            this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + entityW * static_cast<int>(CurrentFrame), top_sprite_posY, -entityW, top_entityH));
            this->sprite.setTextureRect(sf::IntRect(sprite_posX + entityW * static_cast<int>(CurrentFrame), sprite_posY, -entityW, entityH));
        }
        else
        {
            if (CurrentFrame > 4)
            {
                CurrentFrame = 1;
                sitting = true;
            }

            setEntitySpriteCoords(1, 868, 1, 848);
            setEntitySpriteSize(38, 20, 20);
            CurrentFrame += anim_speed * dt * 0.33f;
            this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + entityW * static_cast<int>(CurrentFrame), top_sprite_posY, -entityW, top_entityH));
            this->sprite.setTextureRect(sf::IntRect(sprite_posX + entityW * static_cast<int>(CurrentFrame), sprite_posY, -entityW, entityH));
        }
    }
    break;
    case stay_right:
    {
        setEntitySpriteCoords(1, 664, 1, 644);
        setEntitySpriteSize(38, 17, 19);
        CurrentFrame += anim_speed * dt * 0.33f;
        if (CurrentFrame > 4)
            CurrentFrame = 0;
        this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + entityW * static_cast<int>(CurrentFrame), top_sprite_posY, entityW, top_entityH));
        this->sprite.setTextureRect(sf::IntRect(sprite_posX + entityW * static_cast<int>(CurrentFrame), sprite_posY, entityW, entityH));
    }
    break;
    case stay_left:
    {
        setEntitySpriteCoords(1, 664, 1, 644);
        setEntitySpriteSize(38, 17, 19);
        CurrentFrame += anim_speed * dt * 0.33f;
        if (CurrentFrame > 5)
            CurrentFrame = 1;
        this->spriteTop.setTextureRect(sf::IntRect(top_sprite_posX + entityW * static_cast<int>(CurrentFrame), top_sprite_posY, -entityW, top_entityH));
        this->sprite.setTextureRect(sf::IntRect(sprite_posX + entityW * static_cast<int>(CurrentFrame), sprite_posY, -entityW, entityH));
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
