#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "Pistol.h"
#include "SFML-2.5.1/include/SFML/Graphics.hpp"

class Player : public Character
{
private:
    sf::Sprite spriteTop;
    int top_spriteW = 0, top_spriteH = 0, top_sprite_posX = 0, top_sprite_posY = 0;
    int score, health = 100;

    void initVariables();
    void initSprite();
    void initTopSprite();

public:
    Player() = delete;

    Player(const float &posX, const float &posY, sf::Image &image, sf::String name);

    ~Player();

    // правильный размер игрока ,учитывая накладывания спрайтов(по Y)
    sf::FloatRect getRect();

    // передвижение спрайта(текстуры)
    void setPosition() override;

    // задает координаты спрайта(x , y)
    void setTopSpriteCoords(const int &top_sprite_posX, const int &top_sprite_posY);

    // задает размер спрайтов(низ_ширина,низ_высота,верх_высота)
    void setTopSpriteSize(const int &top_sprite_width, const int &top_sprite_height);

    // включение атаки (состояние)
    void atack(const float &dt) override;

    void topFrameChange(const bool &right);

    // обновление анимации
    void updateAnimation(const float &dt) override;

    // обновление компонентов
    void update(const float &dt) override;

    // отрисовка спрайтов
    void render(sf::RenderTarget *target) override;
};

#endif