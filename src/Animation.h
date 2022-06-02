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

	/// <summary>
	/// Default constructor
	/// </summary>
	Animation();
	
	/// <summary>
	/// Switches a animation frame (sets sprite rectTxt on texture)
	/// </summary>
	/// <param name="s">Reference to animated sprite</param>
	void applyToSprite(sf::Sprite& s);
	
	/// <summary>
	/// Updates the index of a frame if enough time has passed
	/// </summary>
	/// <returns>True if frame has been changed</returns>
	bool update();

	/// <summary>
	/// Starts measuring time
	/// </summary>
	/// <param name="howLong_ms">How much time is to be counted</param>
	void startMeasureTime(int howLong_ms);
	
	/// <summary>
	/// Checks if time determined in startMeasureTime method has passed
	/// </summary>
	/// <returns>True if time has passed</returns>
	bool checkIfTimePassed();
};


#endif // ANIM