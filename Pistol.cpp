#include "Pistol.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Inits_for_Cstr----------------------------------------------------
//---------------------------------------------------------------------------------------------------

void Pistol::initBulletTexture()
{
    sf::Image img;
    if (!img.loadFromFile(R"(img/bullet.png)"))
        throw std::system_error(errno, std::system_category(), "Failed to open ./img/bullet.png");
    img.createMaskFromColor(sf::Color(86, 177, 222));
    this->texture.loadFromImage(img);
    this->texture.setSmooth(true);
}

void Pistol::initSounds()
{
    if (!sound_buf.loadFromFile(R"(sounds/Pistol_Shoot.ogg)"))
        throw std::system_error(errno, std::system_category(), "Failed to open sounds/Pistol_Shoot.ogg");
    shoot_sound.setBuffer(sound_buf);
    shoot_sound.setLoop(false);
    shoot_sound.setVolume(35);
}

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Pistol::Pistol(const unsigned short &dmg, const unsigned short &range) : Weapon("Pistol", dmg, range)
{
    try
    {
        initBulletTexture();
        initSounds();
    }
    catch (const std::system_error &ex)
    {
        std::cerr << "Error in Pistol.cpp." << ex.what() << " (" << ex.code() << ")" << std::endl;
    }
}

Pistol::~Pistol()
{

    while (bullets.size())
    {
        delete bullets.back();
        bullets.pop_back();
    }
}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

const std::list<Bullet *> &Pistol::getBulletList() const { return this->bullets; }

bool Pistol::shootLeft(const unsigned short &posX, const unsigned short &posY, const float &dt)
{
    if (cooldown <= 0)
    {
        shoot_sound.play();
        bullets.push_back(new Bullet(posX, posY, "left", this->getRange(), texture));
        cooldown = atk_speed;
        return true;
    }
    else
        return false;
}

bool Pistol::shootRight(const unsigned short &posX, const unsigned short &posY, const float &dt)
{
    if (cooldown <= 0)
    {
        shoot_sound.play();
        bullets.push_back(new Bullet(posX, posY, "right", this->getRange(), texture));
        cooldown = atk_speed;
        return true;
    }
    else
        return false;
}

// скорее всего течет память
void Pistol::update(const float &dt)
{
    if (cooldown > 0)
        cooldown -= dt;

    for (auto it : bullets)
    {
        if (!it->getAlive())
        {
            delete it;
        }
        else
        {
            it->update(dt);
        }
    }

    bullets.remove_if([](Bullet *it) { return !it->getAlive(); });
}

void Pistol::render(sf::RenderTarget *target)
{
    for (auto it : bullets)
    {
        if (it->getAlive())
        {
            it->render(target);
        }
    }
}