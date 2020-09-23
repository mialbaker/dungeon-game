#ifndef BOGEYMEN_H
#define BOGEYMEN_H
#include "Actor.h"

class Bogeymen : public Actor
{
public:
	Bogeymen(Dungeon* d, int r, int c);

	//mutator
	virtual void move();

private:
	Dungeon* m_dungeon;
	bool m_dead;
};

#endif
