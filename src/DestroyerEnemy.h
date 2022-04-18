#ifndef DESTROYER
#define DESTROYER

#include "Enemy.h"

class DestroyerEnemy : public Enemy 
{
public:
	
	DestroyerEnemy(float _x, float _y, int sp, int type);

	void move(Map* map) override;
	bool changeDirection(int param) override;

	void destroyOnHit();
};






#endif // !DESTROYER

