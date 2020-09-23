#include "Dungeon.h"
#include "utilities.h"
#include "Player.h"
#include "Actor.h"
#include "Snakewomen.h"
#include "Bogeymen.h"
#include "Dragon.h"
#include "Goblin.h"
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

Dungeon::Dungeon(int level)
{
	m_rows = NROWS;
	m_cols = NCOLS;
	m_level = level;
	m_numRooms = randInt(4, 6);
	// Fill displayGrid with '#'
	//initialize grid
	for (int i = 0; i < NROWS; i++)
	{
		for (int j = 0; j < NCOLS; j++)
		{
			m_grid[i][j] = '#';
		}
	}
	//create rooms and corridors
	createRooms();
	//randomize player location
	//make sure to place on an empty grid
	int randRow = randInt(1, 17);
	int randCol = randInt(1, 69);
	while (m_grid[randRow][randCol] != ' ')
	{
		randRow = randInt(1, 17);
		randCol = randInt(1, 69);
	}
	m_player = new Player(this, randRow, randCol);
	addMonsters();
	int randRow2 = randInt(1, 17);
	int randCol2 = randInt(1, 69);
	while (m_grid[randRow2][randCol2] != ' ')
	{
		randRow2 = randInt(1, 17);
		randCol2 = randInt(1, 69);
	}
	m_grid[randRow2][randCol2] = '>';
	setStairRow(randRow2);
	setStairCol(randCol2);
	if (level == 4)
	{
		int randRow3 = randInt(1, 17);
		int randCol3 = randInt(1, 69);
		while (m_grid[randRow3][randCol3] != ' ')
		{
			randRow3 = randInt(1, 17);
			randCol3 = randInt(1, 69);
		}
		m_grid[randRow3][randCol3] = '&';
		setIdolRow(randRow3);
		setIdolCol(randCol3);
	}
}

Dungeon::~Dungeon()
{
	for (int i = 0; i < m_monsters.size(); i++)
		delete m_monsters[i];
}

int Dungeon::getPlayerRow() const
{ 
	return player()->row(); 
}

int Dungeon::getPlayerCol() const
{ 
	return player()->col(); 
}

int Dungeon::rows() const
{
	return m_rows;
}

int Dungeon::cols() const
{
	return m_cols;
}

Player* Dungeon::player() const
{
	return m_player;
}

char Dungeon::getCellStatus(int r, int c) const
{
	checkPos(r, c, "Arena::getCellStatus");
	return m_grid[r][c];
}

void Dungeon::display()
{
	// Indicate player's position
	if (m_player != nullptr)
	{
		for (int i = 0; i < NROWS; i++)
		{
			for (int j = 0; j < NCOLS; j++)
			{
				if (m_grid[i][j] == '@' 
					|| m_grid[i][j] == 'S'
					|| m_grid[i][j] == 'G'
					|| m_grid[i][j] == 'B'
					|| m_grid[i][j] == 'D')
				{
					m_grid[i][j] = ' ';
				}
			}
		}

		int ro = m_player->row();
		int co = m_player->col();
		m_grid[m_player->row()][m_player->col()] = (m_player->isDead() ? 'X' : '@');
	}

	//indicate each monsters position
	for (int i = 0; i < m_numSnakewomen; i++)
	{
		if (!m_monsters[i]->isDead())
			m_grid[m_monsters[i]->row()][m_monsters[i]->col()] = 'S';
	}
	for (int i = m_numSnakewomen; i < m_numGoblins + m_numSnakewomen; i++)
	{
		if (!m_monsters[i]->isDead())
			m_grid[m_monsters[i]->row()][m_monsters[i]->col()] = 'G';
	}
	for (int i = m_numGoblins + m_numSnakewomen; i < m_numGoblins + m_numSnakewomen + m_numBogeymen; i++)
	{
		if (!m_monsters[i]->isDead())
			m_grid[m_monsters[i]->row()][m_monsters[i]->col()] = 'B';
	}
	for (int i = m_numGoblins + m_numSnakewomen + m_numBogeymen; i < m_numGoblins + m_numSnakewomen + m_numBogeymen + m_numDragons; i++)
	{
		if (!m_monsters[i]->isDead())
			m_grid[m_monsters[i]->row()][m_monsters[i]->col()] = 'D';
	}


	// Draw the grid
	clearScreen();
	for (int r = 0; r < rows(); r++)
	{
		for (int c = 0; c < cols(); c++)
			cout << m_grid[r][c];
		cout << endl;
	}

	// Write message & player info
	if (m_player == nullptr)
		cout << "There is no player!" << endl;
	else if (m_player->isDead())
		cout << "The player is dead." << endl;

	//display player stats
	cout << "Dungeon Level: " << m_level << ", "
		<< "Hit points: " << m_player->getHits() << ", "
		<< "Armor: " << m_player->getArmor() << ", "
		<< "Strength: " << m_player->getStrength() << ", "
		<< "Dexterity: " << m_player->getDexterity() << endl;

	//display attacks
	cout << player()->getWeapon()->getAction() << endl;
}

bool Dungeon::addPlayer(int r, int c)
{
	//if it tries to place a player on a full gridpoint
	if (m_grid[r][c] != ' ');
		return false;

	// Don't add a player if one already exists
	if (m_player != nullptr)
		return false;

	m_player = new Player(this, r, c);
	return true;
}

bool Dungeon::addMonsters()
{
	if (m_level == 3 || m_level == 4) //levels 3 and 4 have every type of monster
	{
		//generate randomly placed monsters 
		//determine number of monsters randomly
		int numMonsters = randInt(2, 5 * (m_level + 1) + 1);
		//determine number of snakewomen
		m_numSnakewomen = randInt(1, numMonsters / 3);
		//determine number of goblins
		m_numGoblins = randInt(1, numMonsters / 3);
		//determine number of bogeymen
		m_numBogeymen = randInt(1, numMonsters /3);
		//determine number of dragons
		m_numDragons = numMonsters - (m_numSnakewomen + m_numBogeymen + m_numGoblins);
		//create snakewomen
		for (int i = 0; i < m_numSnakewomen; i++)
		{
			int randRow = randInt(1, 17);
			int randCol = randInt(1, 69);
			while (m_grid[randRow][randCol] != ' ')
			{
				randRow = randInt(1, 17);
				randCol = randInt(1, 69);
			}
			m_monsters.push_back(new Snakewomen(this, randRow, randCol));
		}
		for (int i = 0; i < m_numGoblins; i++)
		{
			int randRow = randInt(1, 17);
			int randCol = randInt(1, 69);
			while (m_grid[randRow][randCol] != ' ')
			{
				randRow = randInt(1, 17);
				randCol = randInt(1, 69);
			}
			m_monsters.push_back(new Goblin(this, randRow, randCol));
		}
		for (int i = 0; i < m_numBogeymen; i++)
		{
			int randRow = randInt(1, 17);
			int randCol = randInt(1, 69);
			while (m_grid[randRow][randCol] != ' ')
			{
				randRow = randInt(1, 17);
				randCol = randInt(1, 69);
			}
			m_monsters.push_back(new Bogeymen(this, randRow, randCol));
		}
		for (int i = 0; i < m_numDragons; i++)
		{
			int randRow = randInt(1, 17);
			int randCol = randInt(1, 69);
			while (m_grid[randRow][randCol] != ' ')
			{
				randRow = randInt(1, 17);
				randCol = randInt(1, 69);
			}
			m_monsters.push_back(new Dragon(this, randRow, randCol));
		}
	}
	if (m_level == 2) //level 2 has bogeymen snakewomen and goblins
	{
		//generate randomly placed monsters 
		//determine number of monsters randomly
		int numMonsters = randInt(2, 5 * (m_level + 1) + 1);
		//determine number of snakewomen
		m_numSnakewomen = randInt(1, numMonsters / 2);
		//determine number of goblins
		m_numGoblins = randInt(1, numMonsters / 2);
		//determine number of bogeymen
		m_numBogeymen = numMonsters - (m_numSnakewomen + m_numGoblins);
		//create snakewomen
		for (int i = 0; i < m_numSnakewomen; i++)
		{
			int randRow = randInt(1, 17);
			int randCol = randInt(1, 69);
			while (m_grid[randRow][randCol] != ' ')
			{
				randRow = randInt(1, 17);
				randCol = randInt(1, 69);
			}
			m_monsters.push_back(new Snakewomen(this, randRow, randCol));
		}
		for (int i = 0; i < m_numGoblins; i++)
		{
			int randRow = randInt(1, 17);
			int randCol = randInt(1, 69);
			while (m_grid[randRow][randCol] != ' ')
			{
				randRow = randInt(1, 17);
				randCol = randInt(1, 69);
			}
			m_monsters.push_back(new Goblin(this, randRow, randCol));
		}
		for (int i = 0; i < m_numBogeymen; i++)
		{
			int randRow = randInt(1, 17);
			int randCol = randInt(1, 69);
			while (m_grid[randRow][randCol] != ' ')
			{
				randRow = randInt(1, 17);
				randCol = randInt(1, 69);
			}
			m_monsters.push_back(new Bogeymen(this, randRow, randCol));
		}
	}
	else //if level 0 or 1 you only have snakewomen and goblins
	{
		//generate randomly placed monsters 
		//determine number of monsters randomly
		int numMonsters = randInt(2, 5 * (m_level + 1) + 1);
		//determine number of snakewomen
		m_numSnakewomen = randInt(1, numMonsters);
		//determine number of goblins
		m_numGoblins = numMonsters - m_numSnakewomen;
		//create snakewomen
		for (int i = 0; i < m_numSnakewomen; i++)
		{
			int randRow = randInt(1, 17);
			int randCol = randInt(1, 69);
			while (m_grid[randRow][randCol] != ' ')
			{
				randRow = randInt(1, 17);
				randCol = randInt(1, 69);
			}
			m_monsters.push_back(new Snakewomen(this, randRow, randCol));
		}
		for (int i = 0; i < m_numGoblins; i++)
		{
			int randRow = randInt(1, 17);
			int randCol = randInt(1, 69);
			while (m_grid[randRow][randCol] != ' ')
			{
				randRow = randInt(1, 17);
				randCol = randInt(1, 69);
			}
			m_monsters.push_back(new Goblin(this, randRow, randCol));
		}
	}
	return true;
}

void Dungeon::moveMonsters()
{
	for (int i = 0; i < m_monsters.size(); i++)
	{
		m_monsters[i]->move();
	}
}

bool Dungeon::isPosInBounds(int r, int c) const
{
	return (r >= 1 && r < m_rows && c >= 1 && c < m_cols);
}

void Dungeon::checkPos(int r, int c, string functionName) const
{
	if (!isPosInBounds(r, c))
	{
		cout << "***** " << "Invalid arena position (" << r << ","
			<< c << ") in call to " << functionName << endl;
		exit(1);
	}
}

//check if rooms overlap
bool Dungeon::squareIntersects(int numRows, int numCols, int topLeftRow, int topLeftCol)
{
	for (int i = topLeftRow - 1; i < topLeftRow + numRows + 1; i++)
	{
		for (int j = topLeftCol - 1; j < topLeftCol + numCols + 1; j++)
		{
			if (m_grid[i][j] == ' ')
			{
				return true;
			}
		}
	}
	return false;
}

void Dungeon::createRooms()
{
	//add rooms
	int roomRows; // = randInt(1, 15); //randomly generate # of rows
	int roomCols; // = randInt(1, 15); //randomly generate # of columns
	int topLeftRow; // = randInt(1, 20); //randomly assign top left corner for location
	int topLeftCol; // = randInt(1, 20); //randomly assign top left corner for location
	vector<pair<int, int>> topLeftCorner; //stores a vector of top left corner coordinates
	int x = 0;

	while (x < m_numRooms)
	{
		//initialize to random values
		roomRows = randInt(5, 9); //randomly generate # of rows
		roomCols = randInt(5, 25); //randomly generate # of columns
		topLeftRow = randInt(1, 18); //randomly assign top left corner for location
		topLeftCol = randInt(1, 70); //randomly assign top left corner for location

		//if out of bounds or they intersect
		if ((topLeftRow + roomRows) > (m_rows - 1) || (topLeftCol + roomCols) > (m_cols - 1)
			|| squareIntersects(roomRows, roomCols, topLeftRow, topLeftCol))
		{
			continue;
		}
		else
		{
			topLeftCorner.push_back(make_pair(topLeftRow, topLeftCol)); //add every top left corner's coordinates

			for (int i = topLeftRow; i < topLeftRow + roomRows; i++)
			{
				for (int j = topLeftCol; j < topLeftCol + roomCols; j++)
				{
					m_grid[i][j] = ' '; //initialize to a space
				}
			}
			//make another room
			x++;
		}
	}

	//sort vector by column
	vector<pair<int, int> > sorted;

	while (topLeftCorner.size()) {

		// find min
		pair<int, int> min = topLeftCorner[0];
		int min_index = 0;
		for (int i = 0; i < topLeftCorner.size(); i++) {
			if (topLeftCorner[i].second < min.second) {
				min = topLeftCorner[i];
				min_index = i;
			}
		}
		sorted.push_back(make_pair(min.first, min.second));
		topLeftCorner.erase(topLeftCorner.begin() + min_index);
	}


	//make corridors
	for (int i = 0; i < sorted.size() - 1; i++)
	{

		pair<int, int> one = sorted[i];
		pair<int, int> two = sorted[i + 1];

		pair<int, int> curr_position = make_pair(one.first, one.second);

		// move up / down
		while (curr_position.first != two.first) {
			m_grid[curr_position.first][curr_position.second] = ' ';

			if (curr_position.first > two.first) {
				curr_position.first--;
			}
			else {
				curr_position.first++;
			}

		}
		// move left / right
		while (curr_position.second != two.second) {
			m_grid[curr_position.first][curr_position.second] = ' ';

			if (curr_position.second > two.second) {
				curr_position.second--;
			}
			else {
				curr_position.second++;
			}

		}
	}
}

