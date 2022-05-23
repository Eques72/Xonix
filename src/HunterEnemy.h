#ifndef HUNT
#define HUNT

#include <memory>
#include "Enemy.h"
#include "Player.h"

class HunterEnemy : public Enemy
{
	int indexLatestTailPiece = -1;

	std::shared_ptr<Player> victim;
	std::pair<int, int> spawnPoint;

public:

	HunterEnemy(float _x, float _y, int sp, std::shared_ptr<Player> p);

	bool changeDirection(int param) override;

	void move(Map& map) override;

	void calmDown();
};


#endif // !HUNT
