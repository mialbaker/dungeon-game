// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "Dungeon.h"
#include "Player.h"
#include <iostream>

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
	if (goblinSmellDistance < 0)
	{
		std::cout << "***** Cannot create Game with negative number of vampires!" << std::endl;
		exit(1);
	}

	// Create dungeon
	m_dungeon = new Dungeon(0);
	m_level = 0;

	// Add player
	int rPlayer;
	int cPlayer;
	do
	{
		rPlayer = randInt(1, NROWS - 1);
		cPlayer = randInt(1, NCOLS - 1);
	} while (m_dungeon->getCellStatus(rPlayer, cPlayer) != ' ');
	m_dungeon->addPlayer(rPlayer, cPlayer);
}

Game::~Game()
{
	delete m_dungeon;
	//delete m_player;
}

bool Game::takePlayerTurn()
{
	for (;;)
	{
		//get the player's move
		char playerMove = getCharacter();

		Player* player = m_dungeon->player();
		int dir;

		//decend down the stairs
		if (playerMove == '>' && m_dungeon->player()->row() == m_dungeon->getStairRow() && m_dungeon->player()->col() == m_dungeon->getStairCol())
		{
			m_level++;
			delete m_dungeon;
			Dungeon* m_dungeon = new Dungeon(m_level);
		}

		if (playerMove == 'g')
		{
			//pick up an object and place it in inventory
			if (m_dungeon->player()->row() == m_dungeon->getIdolRow()
				&& m_dungeon->player()->col() == m_dungeon->getIdolCol())
			{
				std::cout << "You got the golden idol. You win!" << std::endl;
				std::cout << "Press q to exit game." << std::endl;
				while (getCharacter() != 'q')
					;
			}
		}
		if (playerMove == 'w')
		{
			//change weapon
		}
		if (playerMove == 'i')
		{
			//open inventory
		}
		//cheat
		if (playerMove == 'c')
		{
			m_dungeon->player()->setHits(50);
		}
		if (decodeDirection(playerMove, dir)) {
			
			return player->move(dir);
		}
		else
		{
			return false;
		}
	}
}

bool Game::decodeDirection(char ch, int& dir)
{
	switch (tolower(ch))
	{
	default:  return false;
	case 'h': dir = ARROW_LEFT; break;
	case 'j': dir = ARROW_DOWN;  break;
	case 'k': dir = ARROW_UP; break;
	case 'l': dir = ARROW_RIGHT;  break;
	}
	return true;
}

void Game::play()
{
	m_dungeon->display();
	Player* player = m_dungeon->player();
	if (player == nullptr)
		return;
	while (!player->isDead()) 
	{
		takePlayerTurn();
		m_dungeon->display();
		if (player->isDead())
			break;
		m_dungeon->moveMonsters();
		m_dungeon->display();
	}
	if (player->isDead())
	{
		std::cout << "You died." << std::endl;
	}
	else
	{
		std::cout << "You win." << std::endl;
	}
	std::cout << "Press q to exit game." << std::endl;
	while (getCharacter() != 'q')
		;
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
