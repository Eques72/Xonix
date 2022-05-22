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
	
	std::vector<std::unique_ptr<Button>> buttons;

	bool useFrame{ true };
	bool fullFrame{ false };
	sf::RectangleShape frame;

	bool isActive = true;
public:

	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext);
	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel);
	TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext, std::string buttonLabel1, std::string buttonLabel2);

	void turnFrame(bool on_off);
	void fillFrame(bool on_off);

	void setUpText(sf::Text& text, std::string s, float textSize);
	void setUpFrame(int _x, int _y, int _w, int _h);

	void displayTextBox(sf::RenderWindow& win);

	std::pair<bool, int> waitForButton(sf::RenderWindow& win);
};


#endif // !TEXT_BOX
