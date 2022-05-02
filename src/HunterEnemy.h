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
	
	void trackNewTail(Map* m);

	/// <summary>
	/// Calculates coordinates in pixels of certain block by given this block's index as a parameter
	/// </summary>
	/// <param name="index">Index of given block</param>
	/// <returns>Returns x,y coordinates in px</returns>
	std::pair<int, int> calculateTailCoordinates(int index);

	void calmDown();

};


#endif // !HUNT
