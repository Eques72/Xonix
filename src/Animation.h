#ifndef ANIM
#define ANIM

#include <SFML/Graphics.hpp>
#include <chrono>


class Animation
{
	std::chrono::milliseconds holdTime{ 100 };
	int frames{ 8 };

	std::chrono::time_point<std::chrono::steady_clock> startTime;
	int currentFrame{ 0 };

public:
	Animation();
	Animation(int x, int y, sf::Texture& t);

	void applyToSprite(sf::Sprite& s);
	bool update();

	void startMeasureTime(int howLong_ms);
	bool checkIfTimePassed();
};


#endif // ANIM