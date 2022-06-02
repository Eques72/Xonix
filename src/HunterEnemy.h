#ifndef HUNT
#define HUNT

#include <memory>
#include "Enemy.h"
#include "Player.h"

/// <summary>
/// Inherited from "Enemy" class. Represents a entity that follows player character whenever it starts to claim tiles.
/// </summary>
class HunterEnemy : public Enemy
{
	std::shared_ptr<Player> victim;
	std::pair<int, int> spawnPoint;

public:

	HunterEnemy(float _x, float _y, int sp, std::shared_ptr<Player> p);

	/// <summary>
	/// Method unused in this context, always returns false
	/// </summary>
	bool changeDirection(int param) override;

	/// <summary>
	/// Check if any collision occurred, moves entity based on current position of player character (to shorten the distance between entities)	/// </summary>
	/// </summary>
	void move(Map& map) override;

	/// <summary>
	/// In case player character is not in reach, entity next move is to get closer to its initial spawning point
	/// </summary>
	void calmDown();
};


#endif // !HUNT
