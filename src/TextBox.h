#ifndef TEXT_BOX
#define TEXT_BOX

#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "FileManager.h"


class TextBox
{
	sf::Text text;
	sf::Text subtext;
	sf::Font font;
	
	std::unique_ptr<Button> backButton;

	bool useFrame{ true };
	sf::RectangleShape frame;

	bool isActive = true;
public:

	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext);

	void turnFrame(bool on_off);

	void displayTextBox(sf::RenderWindow& win);

	bool waitForButton(sf::RenderWindow& win);
};


#endif // !TEXT_BOX
