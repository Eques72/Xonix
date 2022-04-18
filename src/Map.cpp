#include "Map.h"

void Map::createBackground()
{
	backgroundImage.loadFromFile("resources/BgPic.png");
	backgroundTexture.loadFromImage(backgroundImage);

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(sf::Vector2f(0.f, 0.f));
}

void Map::draw(sf::RenderWindow& win) const
{
	win.draw(backgroundSprite);

	sf::Sprite sprite;
	sf::Texture texture;

	texture.loadFromImage(wallImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));

	int lastDrawnType = 1;

	for (int q{ 0 }; q < MAP_HEIGHT; q++)
	{
		for (int w{ 0 }; w < MAP_WIDTH; w++)
		{
			float x = (float)w * 30;
			float y = (float)q * 30;
			sprite.setPosition(sf::Vector2f(x, y));


			switch (mapping[w + q * MAP_WIDTH])
			{
			case 1:
				if (lastDrawnType != 1)
					sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
				win.draw(sprite);
				lastDrawnType = 1;
				break;
			case 2:
				if (lastDrawnType != 2)
					sprite.setTextureRect(sf::IntRect(30, 0, 30, 30));
				win.draw(sprite);
				lastDrawnType = 2;
				break;
			default:
				break;

			}
		}
	}

}

Map::Map()
{
	createBackground();
	wallImage.loadFromFile("resources/Wall.png");
}

std::array<int, 1620>& Map::getMapping() { return mapping; }

int Map::getTileState(int index)
{
	if (index < mapping.size())
		return mapping[index];
	return -1;
}

void Map::clearTail()
{
	auto d = [](int n) {return n == TAIL_TILE ? EMPTY_TILE : n; };
	std::ranges::transform(mapping, mapping.begin(), d);
}

void Map::fillEmptySpace()
{
	auto d = [](int n) {return n == OCCUPIED_TILE ? EMPTY_TILE : WALL_TILE; };
	std::ranges::transform(mapping, mapping.begin(), d);
}

void Map::changeTileState(int index, int newState) { mapping[index] = newState; }

double Map::getProggres()
{
	auto i = std::ranges::count(mapping, 1);
	return (((double)i / (double)mapping.size()) * 100.0);
}

void Map::resetMap()
{
  FileManager::readMapFile(mapping, "resources/gameSettings/map.txt");
}