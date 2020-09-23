#ifndef ACTOR_H
#define ACTOR_H
#include <string>
#include "Dungeon.h"
#include "Weapons.h"

class Actor
{
public:
	//constructor
	Actor(Dungeon* d, int r, int c);

	//accessors
	int row() const { return m_row; }
	int col() const { return m_col; }
	bool isDead() const { return m_dead; }
	int getHits() const { return m_hits; }
	Weapons* getWeapon() const { return m_currWeapon; }
	int getArmor() const { return m_armor; }
	int getStrength() const { return m_strength; }
	int getDexterity() const { return m_dexterity; }
	std::string getName() const { return m_name; }

	//mutators
	void setRow(int row) { m_row = row; }
	void setCol(int col) { m_col = col; }
	void setDead() { m_dead = true; }
	void setHits(int points) { m_hits = points; }
	void setWeapon(std::string weapon) { m_currWeapon->setName(weapon); }
	void setArmor(int points) { m_armor = points; }
	void setStrength(int points) { m_strength = points; }
	void setDexterity(int points) { m_dexterity = points; }
	void attack(Actor* defense);
	void setName(std::string name) { m_name = name; }
	//pure virtual
	virtual void move() = 0;

private:
	Dungeon* m_dungeon;
	int m_row;
	int m_col;
	bool m_dead;
	//hit points
	int m_hits;
	//current weapon
	Weapons* m_currWeapon;
	//armor points
	int m_armor;
	//strength points
	int m_strength;
	//dexterity points
	int m_dexterity;
	//sleep time
	int m_sleep;
	std::string m_name;

};

#endif
