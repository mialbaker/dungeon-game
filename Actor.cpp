#include "Actor.h"
#include "utilities.h"
#include <iostream>

Actor::Actor(Dungeon* d, int r, int c)
{
	if (d == nullptr)
	{
		std::cout << "***** The actor must be created in some Arena!" << std::endl;
		exit(1);
	}
	if (r < 1 || r > d->rows() || c < 1 || c > d->cols())
	{
		std::cout << "**** Actor created with invalid coordinates (" << r
			<< "," << c << ")!" << std::endl;
		exit(1);
	}
	m_dungeon = d;
	m_row = r;
	m_col = c;
	m_dead = false;
	Weapons* weapon = new Weapons();
	m_currWeapon = weapon;
}

void Actor::attack(Actor* defense)
{
	int attackerPoints = getDexterity() + getWeapon()->getDexterityBonus(getWeapon()->getName());
	int defenderPoints = defense->getDexterity() + defense->getArmor();
	int damagePoints = 0;
	if (randInt(1, attackerPoints) >= randInt(1, defenderPoints))
	{
		//attacker has hit defender
		damagePoints = randInt(0, getStrength() + getWeapon()->getDamageAmt(getWeapon()->getName()) - 1);
	}
	//attacker misses defender, do nothing
	defense->setHits(defense->getHits() - damagePoints);

	if (defense->getHits() <= 0)
	{
		defense->setDead();
		//delete monster
		std::vector<Actor*> monsters = m_dungeon->getMonsters();
		
	}
	
}
