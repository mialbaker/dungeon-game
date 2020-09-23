// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include <string>
#include "Dungeon.h"

// You may add data members and other member functions to this class.
//class Dungeon;

class Game
{
public:
	Game(int goblinSmellDistance);
	~Game();
	void play();
	bool takePlayerTurn();

private:
	Dungeon* m_dungeon;
	int m_level;

	//helper functions
	bool decodeDirection(char ch, int& dir);
};

#endif // GAME_INCLUDED
