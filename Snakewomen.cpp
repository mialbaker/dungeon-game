#include "Snakewomen.h"
#include <iostream>
#include "utilities.h"
using namespace std;

Snakewomen::Snakewomen(Dungeon* d, int r, int c) : Actor(d, r, c)
{
	if (d == nullptr)
	{
		cout << "***** The snakewomen must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > d->rows() || c < 1 || c > d->cols())
	{
		cout << "**** snakewomen created with invalid coordinates (" << r
			<< "," << c << ")!" << endl;
		exit(1);
	}
	//initialize monster attributes
	m_dungeon = d;
	m_dead = false;
	this->setRow(r);
	this->setCol(c);
	this->setHits(randInt(3, 6));
	this->setWeapon("magic fangs");
	this->setArmor(3);
	this->setStrength(2);
	this->setDexterity(3);
	this->setName("Snakewoman");
}

void Snakewomen::move()
{
	int newRow = row();
	int newCol = col();
	//if the player is in range of 1-3 steps
	if (abs(m_dungeon->getPlayerRow() - row()) 
		+ abs(m_dungeon->getPlayerCol() - col()) <= 4
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