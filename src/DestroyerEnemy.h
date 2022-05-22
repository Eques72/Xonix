#ifndef DESTROYER
#define DESTROYER

#include "Enemy.h"

class DestroyerEnemy : public Enemy
{
public:

	DestroyerEnemy(float _x, float _y, int sp, int type);

	void move(Map& map) override;
	bool changeDirection(int param) override;

	/// <summary>
	/// Functions check of whih block(tile) chearacter has bounced. 
	/// </summary>
	/// <returns>Returns pair resemblig type of tile touched and this tile position within an array</returns>
	std::pair<int, int> checkBlockInFront(Map& m, std::pair<int, int> vel);

};
#endif // !DESTROYER

