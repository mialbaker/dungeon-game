#include "Bogeymen.h"
#include "utilities.h"
#include "Player.h"
#include <iostream>
using namespace std;

Bogeymen::Bogeymen(Dungeon* d, int r, int c) : Actor(d, r, c)
{
	if (d == nullptr)
	{
		cout << "***** The bogeyman must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > d->rows() || c < 1 || c > d->cols())
	{
		cout << "**** bogeyman created with invalid coordinates (" << r
			<< "," << c << ")!" << endl;
		exit(1);
	}
	//initialize bogeyman attributes
	m_dungeon = d;
	m_dead = false;
	this->setRow(r);
	this->setCol(c);
	this->setHits(randInt(5, 10));
	this->setWeapon("short sword");
	this->setArmor(2);
	this->setStrength(randInt(2, 3));
	this->setDexterity(randInt(2, 3));
}

void Bogeymen::move()
{
	int newRow = row();
	int newCol = col();
	//if the player is in range of 1-3 steps
	if (abs(m_dungeon->getPlayerRow() - row())
		+ abs(m_dungeon->getPlayerCol() - col()) <= 6
		&& abs(m_dungeon->getPlayerRow() - row())
		+ abs(m_dungeon->getPlayerCol() - col()) > 1)
	{
		if (m_dungeon->getPlayerRow() < row())
		{
			newRow = row() - 1;
		}
		if (m_dungeon->getPlayerRow() > row())
		{
			newRow = row() + 1;
		}
		if (m_dungeon->getPlayerRow() == row())
		{
			if (m_dungeon->getPlayerCol() < col())
			{
				newCol = col() - 1;
			}
			else
			{
				newCol = col() + 1;
			}
		}
		if (m_dungeon->getCellStatus(newRow, newCol) == ' ')
		{
			setRow(newRow);
			setCol(newCol);
		}
	}
	else if (abs(m_dungeon->getPlayerRow() - row())
		+ abs(m_dungeon->getPlayerCol() - col()) == 1)
	{
		attack(m_dungeon->player());
	}
}