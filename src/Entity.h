#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Map.h"

class Entity
{
protected:
	std::pair<int, int> velocity;
	int speed;
	
	sf::Image imageWithTexture;
	sf::Texture texture;
	sf::Sprite body;

	Animation* animation;
	Entity() = delete;

	void loadTextures(std::string path);

public:

	constexpr static int ENTITY_RADIUS = 15;
	Entity(int s);

	virtual void move(Map* map) = 0;

	void draw(sf::RenderWindow& win);

	std::pair<int, int> getDside();
	std::pair<int, int> getUside();
	std::pair<int, int> getLside();
	std::pair<int, int> getRside();

	bool chcekEntityCollions(Entity* e);

	bool checkTailCollisons(Map* map);


	~Entity() { delete animation;  }
};



#endif // !ENTITY