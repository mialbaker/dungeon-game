#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.h"

class Player : public Actor
{
public:
	//constructor
	Player(Dungeon* d, int r, int c);

	//mutators
	bool move(int dir);
	virtual void move();
private:
	Dungeon* m_dungeon;
	bool m_dead;

	//helper functions
	
};

#endif
