#include "Weapon.h"

//---------------------------------------------------------------------------------------------------
//---------------------------------Constructors/Destructors------------------------------------------
//---------------------------------------------------------------------------------------------------

Weapon::Weapon(const std::string &name, const unsigned short &dmg, const unsigned short &range) : name(name), dmg(dmg), range(range) {}

Weapon::~Weapon() {}

//---------------------------------------------------------------------------------------------------
//--------------------------------------------Methods------------------------------------------------
//---------------------------------------------------------------------------------------------------

const std::string &Weapon::getName() const { return this->name; }
const unsigned short &Weapon::getDmg() const { return this->dmg; }
const unsigned short &Weapon::getRange() const { return this->range; }
