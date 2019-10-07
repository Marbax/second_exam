#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Pistol.h"

class Player : public Entity
{
private:
    Weapon *weapon;
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
    float CurrentFrame = 0.0f, anim_speed = 0.02f, jump_speed = 0.3f, jumpH = 22.0f, cur_jumpH = 0.0f;
    bool attacking = false;

public:
    // явное отключение конструктора по умолчанию
    Player() = delete;

    Player(float posx, float posY, sf::Image &image, sf::String name);

    ~Player();

    void setOnGround(bool b);

    bool isOnGround() const;

    // правильный размер игрока ,учитывая накладывания спрайтов(по Y)
    sf::FloatRect getRect();

    // передвижение спрайта(текстуры)
    void setPosition() override;

    // задает координаты спрайта(x , y)
    void setEntitySpriteCoords(int sprite_posX, int sprite_posY, int top_sprite_posX, int top_sprite_posY);

    // задает размер спрайтов(низ_ширина,низ_высота,верх_высота)
    void setEntitySpriteSize(int entity_width, int entity_height, int top_entity_height);

    // движение обьекта(координаты) и смена состояний
    void move(const float boostX, const float boostY, const float &dt) override;

    // кое-какие прыжки
    void updateJumps(const float &dt);

    // включение атаки (состояние)
    void atack(const float &dt);

    // void control(const float &dt);

    // обновление анимации
    void updateAnimation(const float &dt);

    // обновление компонентов
    void update(const float &dt) override;

    // отрисовка спрайтов
    void render(sf::RenderTarget *target) override;

};

#endif