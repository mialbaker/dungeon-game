#include "Weapons.h"
#include "utilities.h"
#include "Actor.h"

Weapons::Weapons() 
{
	std::vector<int> mace;
	mace.push_back(0);
	mace.push_back(2);
	weapons["mace"] = mace;

	std::vector<int> shortSword;
	shortSword.push_back(0);
	shortSword.push_back(2);
	weapons["short sword"] = shortSword;

	std::vector<int> longSword;
	longSword.push_back(2);
	longSword.push_back(4);
	weapons["long sword"] = longSword;

	std::vector<int> magicAxe;
	magicAxe.push_back(2);
	magicAxe.push_back(4);
	weapons["magic axe"] = magicAxe;

	std::vector<int> magicFangs;
	magicFangs.push_back(2);
	magicFangs.push_back(4);
	weapons["magic fangs"] = magicFangs;

}

void Weapons::setAction(Actor* attacker, Actor* defense) 
{ 
	m_actionString = attacker->getName() + " slashes " + attacker->getWeapon()->getName() + " at " + defense->getName(); //and hits or misses
}
void Weapons::setDexterityBonus(std::string weaponName) 
{ 
	m_dexterityBonus = weapons[weaponName][0]; 
}
void Weapons::setDamageAmt(std::string weaponName) 
{ 
	m_damageAmt = weapons[weaponName][1]; 
}

