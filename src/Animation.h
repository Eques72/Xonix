#ifndef ANIM
#define ANIM

#include <SFML/Graphics.hpp>
#include <chrono>


class Animation
{
	static constexpr std::chrono::milliseconds holdTime{ 100 };
	int frames{ 8 };

	std::chrono::time_point<std::chrono::steady_clock> startTime;
	int currentFrame{ 0 };

public:
	Animation(int x, int y, sf::Texture& t);

	void applyToSprite(sf::Sprite& s);
	bool update();

	void setCustomFrames(int num_of_frames);
	void setAnimationRate(float time);
};


#endif // ANIM