#ifndef DRAGON_H
#define DRAGON_H
#include "Actor.h"

class Dragon : public Actor
{
public:
	Dragon(Dungeon* d, int r, int c);

	//mutator
	virtual void move();

private:
	Dungeon* m_dungeon;
	bool m_dead;
};

#endif
