#ifndef GOBLIN_H
#define GOBLIN_H
#include "Actor.h"

class Goblin : public Actor
{
public:
	Goblin(Dungeon* d, int r, int c);
	virtual void move();
	bool isPath(int row, int col, int steps);
private:
	Dungeon* m_dungeon;
	bool m_dead;
};

#endif
