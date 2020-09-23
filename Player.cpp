#include "Player.h"
#include <iostream>
#include "utilities.h"
using namespace std;

Player::Player(Dungeon* d, int r, int c)
	: Actor(d, r, c)
{
	if (d == nullptr)
	{
		cout << "***** The player must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > d->rows() || c < 1 || c > d->cols())
	{
		cout << "**** Player created with invalid coordinates (" << r
			<< "," << c << ")!" << endl;
		exit(1);
	}
	//initialize player attributes
	m_dungeon = d;
	m_dead = false;
	this->setRow(r);
	this->setCol(c);
	this->setHits(20);
	this->setWeapon("short sword");
	this->setArmor(2);
	this->setStrength(2);
	this->setDexterity(2);
}


bool Player::move(int dir)
{
	int rnew = row();
	int cnew = col();
	switch (dir)
	{
	case ARROW_UP:
		if (row() <= 1)
		{
			return false;
		}
		else
		{
			rnew--;
			break;
		}
	case ARROW_RIGHT:
		if (col() + 2 >= m_dungeon->cols())
		{
			return false;
		}
		else
		{
			cnew++;
			break;
		}
	case ARROW_DOWN:
		if (row() + 2 >= m_dungeon->rows())
		{
			return false;
		}
		else
		{
			rnew++;
			break;
		}
	case ARROW_LEFT:
		if (col() <= 1)
		{
			return false;
		}
		else
		{
			cnew--;
			break;
		}
	}
	if (m_dungeon->getCellStatus(rnew, cnew) == '#')
	{
		return false;
	}
	if (m_dungeon->getCellStatus(rnew, cnew) == 'S'
		|| m_dungeon->getCellStatus(rnew, cnew) == 'G'
		|| m_dungeon->getCellStatus(rnew, cnew) == 'B'
		|| m_dungeon->getCellStatus(rnew, cnew) == 'D')
	{
		for (int i = 0; i < m_dungeon->getMonsters().size(); i++)
		{
			if (m_dungeon->getMonsters()[i]->row() == rnew
				&& m_dungeon->getMonsters()[i]->col() == cnew)
			{
				attack(m_dungeon->getMonsters()[i]);
				return true;
			}
		}
		return false;
	}
	setRow(rnew);
	setCol(cnew);
	return true;
}

void Player::move()
{

	return;
}

