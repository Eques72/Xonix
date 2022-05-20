#include "TextBox.h"



TextBox::TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext)
{
	font.loadFromFile("resources/DIGIB.TTF");

	text.setFont(font);
	text.setCharacterSize(150);
	text.setFillColor(sf::Color(100, 200, 200));
	text.setStyle(sf::Text::Bold);

	//place text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
	text.setPosition(_x + _w/2, _y + _h / 8);

	
	subtext.setFont(font);
	subtext.setCharacterSize(60);
	subtext.setFillColor(sf::Color(100, 200, 200));
	subtext.setStyle(sf::Text::Bold);

	//place text
	textRect = subtext.getLocalBounds();
	subtext.setOrigin(textRect.width / 2, textRect.height / 2);
	subtext.setPosition(_x + _w / 2, _y + _h / 2);

	frame.setPosition(_x, _y);
	frame.setOutlineColor(sf::Color(100, 200, 200));
	frame.setOutlineThickness(15.f);
	frame.setSize(sf::Vector2f(_w, _h));
	
	backButton = std::make_unique<Button>(_x - 50 + _w / 2, _y + _h - 100, 100, 100, sf::Color(0, 0, 0), "Back");
	backButton->setActive();
}

void TextBox::turnFrame(bool on_off)
{
	useFrame = on_off;
}

void TextBox::displayTextBox(sf::RenderWindow& win)
{
	win.draw(text);
	backButton->displayButton(win);
	
	if(useFrame)
		win.draw(frame);
}

void TextBox::waitForKeyLoop(sf::RenderWindow& win)
{
	bool loop_active = true;
	while (loop_active)
	{
		printf("we do stuff");
		if (backButton->checkIfButtonPressed(win))
			loop_active = false;
	}
}