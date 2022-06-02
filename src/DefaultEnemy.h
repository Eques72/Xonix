#ifndef GUARD
#define GUARD

#include "Enemy.h"

/// <summary>
/// Inherited from "Enemy" class. Represents a entity that bouces form wall tiles.
/// </summary>
class DefaultEnemy : public Enemy
{
public:

	DefaultEnemy(float _x, float _y, int sp);

	/// <summary>
	/// Entity moves by vector given in velocity variable, bouces of any walls
	/// </summary>
	void move(Map& map) override;
	
	/// <summary>
	/// Changes entity velcity any time a collison with a tile occured (swaps velocity values)
	/// </summary>
	/// <param name="param">Param says if collision was horizontal or vertical</param>
	bool changeDirection(int param) override;
};

#endif // !GUARD
