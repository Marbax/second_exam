#ifndef ARABIAN_H
#define ARABIAN_H

#include "Character.h"
#include "Pistol.h"

class Arabian : public Character
{
private:
    bool loop;
    void initVariables();

protected:
public:
    Arabian() = delete;

    Arabian(const float &posX, const float &posY, sf::Image &image);

    ~Arabian();

    void bestAIever(const float &dt);

    Pistol &getWeapon();

    // void control(const float &dt);

    void movingAnimation(const bool &right, const float &dt);

    void idleAnimation(const bool &right, const float &dt);

    void animate(const bool &right, const unsigned short &frames_count, const float &dt);
    void animateLoop(const bool &right, const unsigned short &frames_count, const float &dt);

    // обновление анимации
    void updateAnimation(const float &dt) override;

    // обновление компонентов
    void update(const float &dt) override;

    // отрисовка спрайтов
    void render(sf::RenderTarget *target) override;
};

#endif