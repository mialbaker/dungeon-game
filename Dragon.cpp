#include "Dragon.h"
#include "utilities.h"
#include "Player.h"
#include <iostream>
using namespace std;

Dragon::Dragon(Dungeon* d, int r, int c) : Actor(d, r, c)
{
	if (d == nullptr)
	{
		cout << "***** The dragon must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > d->rows() || c < 1 || c > d->cols())
	{
		cout << "**** dragon created with invalid coordinates (" << r
			<< "," << c << ")!" << endl;
		exit(1);
	}
	//initialize dragon attributes
	m_dungeon = d;
	m_dead = false;
	this->setRow(r);
	this->setCol(c);
	this->setHits(randInt(20, 25));
	this->setWeapon("long sword");
	this->setArmor(4);
	this->setStrength(4);
	this->setDexterity(4);
}

void Dragon::move()
{

	//if the player is next to dragon
	if (abs(m_dungeon->getPlayerRow() - row())
		+ abs(m_dungeon->getPlayerCol() - col()) == 1)
	{
		if ((m_dungeon->getCellStatus(row(), col()) == '@'))
		{
			attack(m_dungeon->player());
		}
	}
}