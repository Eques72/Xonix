#include "TextBox.h"



TextBox::TextBox(int _x, int _y, int _w, int _h, std::string _text, std::string _subtext)
{
	FileManager::openTTFfile(font, "resources/DIGIB.TTF");
	
	text.setFont(font);
	text.setCharacterSize(150);
	text.setFillColor(sf::Color(100, 200, 200));
	text.setStyle(sf::Text::Bold);
	text.setString(_text);

	//place text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2, textRect.height / 2);
	text.setPosition(_x + _w/2, _y + _h / 8);

	
	subtext.setFont(font);
	subtext.setCharacterSize(60);
	subtext.setFillColor(sf::Color(100, 200, 200));
	subtext.setStyle(sf::Text::Bold);
	subtext.setString(_subtext);

	//place text
	textRect = subtext.getLocalBounds();
	subtext.setOrigin(textRect.width / 2, textRect.height / 2);
	subtext.setPosition(_x + _w / 2, _y + _h / 2);

	frame.setPosition(_x, _y);
	frame.setOutlineColor(sf::Color(100, 200, 200));
	frame.setOutlineThickness(15.f);
	frame.setSize(sf::Vector2f(_w, _h));
	frame.setFillColor(sf::Color::Transparent);
	
	backButton = std::make_unique<Button>(_x - 150 + _w / 2, _y + _h - 150, sf::Color(113, 114, 168), "Back");
	backButton->setActive();
}

void TextBox::turnFrame(bool on_off)
{
	useFrame = on_off;
}

void TextBox::displayTextBox(sf::RenderWindow& win)
{
	if (useFrame)
		win.draw(frame);

	win.draw(text);
	win.draw(subtext);
	backButton->displayButton(win);
}

bool TextBox::waitForButton(sf::RenderWindow& win)
{
		if (backButton->checkIfButtonPressed(win))
			isActive = false;
		return isActive;
}