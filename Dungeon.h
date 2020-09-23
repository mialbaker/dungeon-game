#ifndef DUNGEON_H
#define DUNGEON_H
#include "globalVars.h"
//#include "Player.h"
//#include "Actor.h"
#include <string>
#include <vector>

class Player;
class Actor;

class Dungeon
{
public:
	//Constructor
	Dungeon(int level);
	//Destructor
	~Dungeon();

	//Accessors
	int rows() const;
	int cols() const;
	Player* player() const;
	int getPlayerRow() const;// { return player()->row(); }
	int getPlayerCol() const;// { return player()->col(); }
	char getCellStatus(int r, int c) const;
	void display();
	std::vector<Actor*> getMonsters() const { return m_monsters; }
	int getStairRow() const { return m_stairRow; }
	int getStairCol() const { return m_stairCol; }
	int getIdolRow() const { return m_idolRow; }
	int getIdolCol() const { return m_idolCol; }

	//Mutators
	bool addPlayer(int r, int c);
	bool addMonsters();
	void moveMonsters();
	void setStairRow(int row) { m_stairRow = row; }
	void setStairCol(int col) { m_stairCol = col; }
	void setIdolRow(int row) { m_idolRow = row; }
	void setIdolCol(int col) { m_idolCol = col; }

private:
	char m_grid[NROWS][NCOLS];
	int m_rows;
	int m_cols;
	int m_numRooms;
	Player* m_player;
	int m_level;
	std::vector<Actor*> m_monsters;
	int m_numSnakewomen;
	int m_numGoblins;
	int m_numBogeymen;
	int m_numDragons;
	int m_stairRow;
	int m_stairCol;
	int m_idolRow;
	int m_idolCol;

	//Helper functions
	void checkPos(int r, int c, std::string functionName) const;
	bool isPosInBounds(int r, int c) const;
	bool squareIntersects(int numRows, int numCols, int topLeftRow, int topLeftCol);
	void createRooms();
};

#endif