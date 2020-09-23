#ifndef WEAPONS_H
#define WEAPONS_H
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "GameObject.h"
//#include "Actor.h"

class Actor;

class Weapons : public GameObject
{
public:
	//constructor
	Weapons();

	//getters
	std::string getName() const { return m_name; }
	std::string getAction() const { return m_actionString; }
	int getDexterityBonus(std::string weaponName) { return weapons[weaponName][0]; }
	int getDamageAmt(std::string weaponName) { return weapons[weaponName][1]; }

	//setters
	void setName(std::string name) { m_name = name; }
	void setAction(Actor* attacker, Actor* defense);// { m_actionString = action; }
	void setDexterityBonus(std::string weaponName);// { m_dexterityBonus = dexterityBonus; }
	void setDamageAmt(std::string weaponName);// { m_damageAmt = damageAmt; }

private:
	std::string m_name;
	std::string m_actionString;
	int m_dexterityBonus;
	int m_damageAmt;
	std::unordered_map<std::string, std::vector<int>> weapons;
};

#endif