#include "DestroyerEnemy.h"

DestroyerEnemy::DestroyerEnemy(float _x, float _y, int sp, int type) :Enemy(sp, type)
{
	std::random_device rand_dev;
	std::mt19937       generator(rand_dev());

	int range_from = Map::TILE_SIZE * 2;
	int range_to_X = Map::MAP_WIDTH_PIXELS - (Map::TILE_SIZE * 2);
	int range_to_Y = Map::MAP_HEIGHT_PIXELS - (Map::TILE_SIZE * 2);

	std::uniform_int_distribution<>  _X(range_from, range_to_X);
	std::uniform_int_distribution<>  _Y(range_from, range_to_Y);

	//	float tab[12][2] = { {1.0, 1.0},{-1.0, -1.0},{-1.0, 1.0},{1.0, -1.0},
		//	{-2.0, 0.5},{-2.0, 0.5},{2.0, 0.5},{2.0, -0.5}, 
			//{0.5, 2.0},{-0.5, 2.0},{0.5, -2.0},{-0.5, -2.0}	};
	float tab[2] = { -1, 1 };

	std::uniform_int_distribution<>  _Dir(0, 1);
	//	std::uniform_int_distribution<>  _Dir(0, 11);
	//	int _GetDir = _Dir(generator);

	//	velocity = std::make_pair(tab[_GetDir][0], tab[_GetDir][1]);
	velocity = std::make_pair(tab[_Dir(generator)], tab[_Dir(generator)]);

	loadTextures("resources/enemy.png");
	body.setColor(sf::Color::Magenta);
	body.setOrigin(15, 15);
	body.setPosition(sf::Vector2f(_X(generator), _Y(generator)));
}

void DestroyerEnemy::move(Map* map)
{
	std::pair<int, int> oldVeclocity = velocity;

	if (!changeDirection(checkWallCollisons(map)))
		body.setPosition(sf::Vector2f(body.getPosition().x + (speed * velocity.first),
			body.getPosition().y + (speed * velocity.second)));
	else
	{
		std::pair<int, int> tileInfo = checkBlockInFront(map, oldVeclocity);
		if (tileInfo.first == Map::WALL_TILE && map->isTileInOuterRing(tileInfo.second) == false)
			map->changeTileState(tileInfo.second, Map::EMPTY_TILE);
	}
}

std::pair<int, int> DestroyerEnemy::checkBlockInFront(Map* m, std::pair<int, int> vel)
{
	sf::Vector2f pos = body.getPosition();
	pos.x += speed * vel.first;
	pos.y += speed * vel.second;

	if (vel.second >= 1)
		pos.y += Entity::ENTITY_RADIUS;
	else if (vel.second <= -1)
		pos.y -= Entity::ENTITY_RADIUS;
	if (vel.first >= 1)
		pos.x += Entity::ENTITY_RADIUS;
	else if (vel.first <= -1)
		pos.x -= Entity::ENTITY_RADIUS;

	int X = ((int)pos.x - (int)pos.x % Map::TILE_SIZE) / Map::TILE_SIZE;
	int Y = ((int)pos.y - (int)pos.y % Map::TILE_SIZE) / Map::TILE_SIZE;
	int index = X + Y * Map::MAP_WIDTH;

	int tileType = m->getTileState(index);

	return std::make_pair(tileType, index);
}


bool DestroyerEnemy::changeDirection(int param)
{
	if (param == 1)
	{
		velocity.second *= -1;
		return true;
	}

	else if (param == 2)
	{
		velocity.first *= -1;
		return true;
	}
	return false;
}
