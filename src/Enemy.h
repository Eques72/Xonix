#ifndef ENEMY_DEFAULT
#define ENEMY_DEFAULT

#include <random>
#include <iostream>
#include "Entity.h"

class Enemy : public Entity
{

protected:

	int enemyType;

	Enemy(int speed, int type) : Entity(speed), enemyType(type) {};

	virtual bool changeDirection(int param) = 0;

	int checkWallCollisons(Map* map);

public:
	int getIndexOfTile();
};

#endif // !ENEMY_DEFAULT
