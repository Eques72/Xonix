#ifndef GUARD
#define GUARD

#include "Enemy.h"


class DefaultEnemy : public Enemy
{
public:

	DefaultEnemy(float _x, float _y, int sp, int type);

	void move(Map* map) override;
	bool changeDirection(int param) override;
};


#endif // !GUARD
