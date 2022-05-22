#include "HunterEnemy.h"

HunterEnemy::HunterEnemy(float _x, float _y, int sp, int type, std::shared_ptr<Player> p) :Enemy(sp, type)
{
	victim = p;

	std::random_device rand_dev;
	std::mt19937       generator(rand_dev());

	int range_from_X = Map::MAP_WIDTH_PIXELS / 4;
	int range_from_Y = Map::MAP_HEIGHT_PIXELS / 4;
	int range_to_X = Map::MAP_WIDTH_PIXELS - Map::MAP_WIDTH_PIXELS / 4;
	int range_to_Y = Map::MAP_HEIGHT_PIXELS - Map::MAP_HEIGHT_PIXELS / 4;

	std::uniform_int_distribution<>  _X(range_from_X, range_to_X);
	std::uniform_int_distribution<>  _Y(range_from_Y, range_to_Y);

	velocity = std::make_pair(0, 0);

	loadTextures("resources/enemyHunt.png");
	body.setOrigin(15, 15);
	spawnPoint.first = _X(generator);
	spawnPoint.second = _Y(generator);

	body.setPosition(sf::Vector2f(spawnPoint.first, spawnPoint.second));
}

void HunterEnemy::move(Map& map)
{
	std::pair<int, int> pl = victim->checkTileBellow(map);
	if (pl.second == Map::WALL_TILE)
		calmDown();
	else
	{
		//for X
		if (body.getPosition().x > victim->getPositionPx().first)
			velocity.first = -1;
		else if (body.getPosition().x < victim->getPositionPx().first)
			velocity.first = 1;
		else
			velocity.first = 0;
		//for Y
		if (body.getPosition().y > victim->getPositionPx().second)
			velocity.second = -1;
		else if (body.getPosition().y < victim->getPositionPx().second)
			velocity.second = 1;
		else
			velocity.second = 0;
	}

	if (checkWallCollisons(map) == 0)
		body.setPosition(sf::Vector2f(body.getPosition().x + (speed * velocity.first),
			body.getPosition().y + (speed * velocity.second)));
}


bool HunterEnemy::changeDirection(int param) { return false; }


void HunterEnemy::calmDown()
{
	if (body.getPosition().x > spawnPoint.first)
		velocity.first = -1;
	else if (body.getPosition().x < spawnPoint.first)
		velocity.first = 1;
	else
		velocity.first = 0;
	//for Y
	if (body.getPosition().y > spawnPoint.second)
		velocity.second = -1;
	else if (body.getPosition().y < spawnPoint.second)
		velocity.second = 1;
	else
		velocity.second = 0;


}