#ifndef BUT
#define BUT

#include <memory>
#include <SFML/Graphics.hpp>
#include "FileManager.h"

class Button
{
	int x{ 0 };
	int y{ 0 };

	const int width{ 300 };
	const int height{ 150 };
	std::string label{"BUTTON"};

	bool active = true;
	sf::Color color = sf::Color::White;

	sf::Sprite bodyButton;
	sf::Text buttonText;
	sf::Image img;
	sf::Texture tx;
	sf::Font f;
public:

	Button(int _x, int _y, sf::Color c, std::string _label);

	void displayButton(sf::RenderWindow& win);
	
	bool checkIfButtonPressed(sf::RenderWindow& win);

	inline void setActive() 
	{
		active = true;
	}

    inline void setInactive() 
	{
		active = false;
	}
};


#endif // !BUT
