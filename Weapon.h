#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>

class Weapon
{
private:
    std::string name;
    unsigned short dmg;
    unsigned short range;

protected:
public:
    Weapon() = delete;
    Weapon(const std::string &name, const unsigned short &dmg, const unsigned short &range);
    virtual ~Weapon() = 0;

    virtual const std::string &getName() const;
    virtual const unsigned short &getDmg() const;
    virtual const unsigned short &getRange() const;
};

#endif