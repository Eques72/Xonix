#include "DefaultEnemy.h"

	DefaultEnemy::DefaultEnemy(float _x, float _y, int sp, int type) :Enemy(sp, type)
	{
		std::random_device rand_dev;
		std::mt19937       generator(rand_dev());

		int range_from = Map::TILE_SIZE * 2;
		int range_to_X = Map::MAP_WIDTH_PIXELS - (Map::TILE_SIZE * 2);
		int range_to_Y = Map::MAP_HEIGHT_PIXELS - (Map::TILE_SIZE * 2);

		std::uniform_int_distribution<>  _X(range_from, range_to_X);
		std::uniform_int_distribution<>  _Y(range_from, range_to_Y);

		int tab[2] = { -1, 1 };
		std::uniform_int_distribution<>  _Dir(0, 1);

		velocity = std::make_pair(tab[_Dir(generator)], tab[_Dir(generator)]);

		loadTextures("resources/enemy.png");
		body.setOrigin(15, 15);
		body.setPosition(sf::Vector2f(_X(generator), _Y(generator)));
	}

	void DefaultEnemy::move(Map* map)
	{
		if (!changeDirection(checkWallCollisons(map)))
			body.setPosition(sf::Vector2f(body.getPosition().x + (speed * velocity.first),
				body.getPosition().y + (speed * velocity.second)));
	}

	bool DefaultEnemy::changeDirection(int param)
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
