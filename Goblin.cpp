#include "Goblin.h"
#include "utilities.h"
#include "Dungeon.h"
#include "Player.h"
#include <iostream>
#include <queue>
#include <map>
using namespace std;

Goblin::Goblin(Dungeon* d, int r, int c) : Actor(d, r, c)
{
	if (d == nullptr)
	{
		cout << "***** The goblin must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > d->rows() || c < 1 || c > d->cols())
	{
		cout << "**** goblin created with invalid coordinates (" << r
			<< "," << c << ")!" << endl;
		exit(1);
	}
	//initialize player attributes
	m_dungeon = d;
	m_dead = false;
	this->setRow(r);
	this->setCol(c);
	this->setHits(randInt(15, 20));
	this->setWeapon("short sword");
	this->setArmor(1);
	this->setStrength(3);
	this->setDexterity(1);
}

void Goblin::move()
{

	if (isPath(row(), col(), 0)) 
	{
		int newRow = row();
		int newCol = col();
		//if the player is in range of 1-3 steps
		if (abs(m_dungeon->getPlayerRow() - row())
			+ abs(m_dungeon->getPlayerCol() - col()) <= 15
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
}

// recursive function
bool Goblin::isPath(int row, int col, int steps)
{
	if (row == 18 || col == 70 || row < 1 || col < 1) {
		return false;
	}

	if (m_dungeon->getCellStatus(row, col) == '@') {
		return true;
	}
	if (m_dungeon->getCellStatus(row, col) != ' ' && row != this->row() && col != this->col()) {
		return false;
	}
	if (steps >= 7) {
		return false;
	}
	return isPath(row + 1, col, steps + 1) || isPath(row - 1, col, steps + 1)
		|| isPath(row, col + 1, steps + 1) || isPath(row, col - 1, steps + 1);
}

