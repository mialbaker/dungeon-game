#ifndef SNAKEWOMEN_H
#define SNAKEWOMEN_H
#include "Actor.h"
#include "Player.h"

class Snakewomen : public Actor
{
public:
	//constructor
	Snakewomen(Dungeon* d, int r, int c);

	//mutator
	virtual void move();

private:
	Dungeon* m_dungeon;
	bool m_dead;
};

#endif
