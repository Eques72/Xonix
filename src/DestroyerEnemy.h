#ifndef DESTROYER
#define DESTROYER

#include "Enemy.h"

/// <summary>
/// Inherited from "Enemy" class. Represents a entity that destroys any wall tiles it touches
/// </summary>
class DestroyerEnemy : public Enemy
{
public:

	DestroyerEnemy(float _x, float _y, int sp);

	/// <summary>
	/// Check if any collision occurred, moves entity by a vector/// </summary>
	/// </summary>
	void move(Map& map) override;
	
	/// <summary>
	/// Changes entity velcity any time a collison with a tile occured (swaps velocity values)
	/// </summary>
	/// <param name="param">Param says if collision was horizontal or vertical</param>
	bool changeDirection(int param) override;

	/// <summary>
	/// Functions check of whih block(tile) chearacter has bounced. 
	/// </summary>
	/// <returns>Returns pair resemblig type of tile touched and this tile position within an array</returns>
	std::pair<int, int> checkBlockInFront(Map& m, std::pair<int, int> vel);

};
#endif // !DESTROYER

