#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include <array>
#include <ranges>
#include "FileManager.h"
#include "Animation.h"

class Map
{
	sf::Image backgroundImage;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Image wallImage;
	sf::Image tailImage;

	std::array<int, 1620> mapping;
	void createBackground();

public:
	const static int MAP_WIDTH = 54; //in blocks
	const static int MAP_HEIGHT = 30;//in blocks
	const static int MAP_WIDTH_PIXELS = 1620; //in blocks
	const static int MAP_HEIGHT_PIXELS = 900;//in blocks

	const static int TILE_SIZE = 30; //in px

	const static int WALL_TILE = 1;
	const static int TAIL_TILE = 2;
	const static int EMPTY_TILE = 0;
	const static int CRUMBLING_TILE = 3;
	const static int OCCUPIED_TILE = -1;

	void draw(sf::RenderWindow& win) const;

	Map();

	std::array<int, 1620>& getMapping();

	int getTileState(int index);

	void clearTail();

	void fillEmptySpace();
	void changeTileState(int index, int newState);

	double getProggres();

	void resetMap();

	bool isTileInOuterRing(int index);


};

#endif // !MAP
