#ifndef HUNT
#define HUNT

#include "Enemy.h"
#include "Player.h"

class HunterEnemy : public Enemy
{
	int indexLatestTailPiece = -1;

	Player* victim = nullptr;
	std::pair<int, int> spawnPoint;

public:

	HunterEnemy(float _x, float _y, int sp, int type, Player* p);

	void move(Map* map) override;

	/// <summary>
	/// Function useless in this context
	/// </summary>
	bool changeDirection(int param) override;

	void calmDown();

};


#endif // !HUNT
