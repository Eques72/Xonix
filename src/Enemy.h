#ifndef ENEMY_DEFAULT
#define ENEMY_DEFAULT

#include <random>
#include <iostream>
#include "Entity.h"

class Enemy : public Entity
{

protected:

	Enemy(int speed) : Entity(speed) {};

	virtual bool changeDirection(int param) = 0;

	int checkWallCollisons(Map& map);

	int getRandomStartingPos(int rangeFrom, int rangeTo);

public:
	int getIndexOfTile();
};

#endif // !ENEMY_DEFAULT
