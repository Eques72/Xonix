#ifndef MENU
#define MENU

#include <array>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GWindow.h"
class Menu 
{
	const static int width{ 1620 };
	const static int height{ 1100 };
	const std::array<std::string, 4> credits = { "Game created by: " ,"Adran Zareba" ,"as a project for Computer Programming IV lecture" ,"See more at: https://github.com/Eques72" };
	int status = 1; //1 - active, schow buttons, 2 - active, show credits, 0 - inactive
	std::pair<bool,bool> menuChoices = std::make_pair(false,false); //(active = 1, inactive = 0)

	sf::Texture backgroundTx;
	sf::Sprite backgroundSprite;
	std::array<std::unique_ptr<Button>,5> buttons;

	sf::Font font;
	sf::Text menuText;
	sf::Text creditsText;

public:
	Menu() 
	{	
		buttons[0] = std::make_unique<Button>( (width / 2 - 300 - 50), height / 2 - 25 - 150, 300,150, sf::Color(113, 114, 168), "Start");
		buttons[1] = std::make_unique<Button>( (width / 2 + 50), height / 2 - 25 - 150, 300, 150, sf::Color(113, 114, 168), "Continue");
		buttons[2] = std::make_unique<Button>( (width / 2 - 300 - 50), height / 2 + 25, 300, 150, sf::Color(113, 114, 168), "Credits");
		buttons[3] = std::make_unique<Button>( (width / 2 + 50), height / 2 + 25, 300, 150, sf::Color(113, 114, 168), "Exit");
		buttons[4] = std::make_unique<Button>(( 0 + 50), 900 - 200, 300, 150, sf::Color(113, 114, 168), "Back");
		
		buttons[4]->setInactive();


		font.loadFromFile("resources/DIGIB.TTF");
		menuText.setFont(font);
		menuText.setString("-  -  -  XONIX  -  -  -");
		menuText.setCharacterSize(150);
		menuText.setFillColor(sf::Color(127, 224, 227));
		menuText.setStyle(sf::Text::Bold);
		//center text
		sf::FloatRect textRect = menuText.getLocalBounds();
		menuText.setOrigin(textRect.width / 2, textRect.height / 2);
		menuText.setPosition(sf::Vector2f(width / 2, 100));

		creditsText = menuText;
		//creditsText.setFillColor(sf::Color::White);

		backgroundTx.loadFromFile("resources/menuImg.png");
		backgroundSprite.setTexture(backgroundTx);
		
	}

	void displayMenu(sf::RenderWindow& win) 
	{
		win.draw(backgroundSprite);

		if (status == 1)
		{
			win.draw(menuText);

			for (size_t i{ 0 }; i < buttons.size() - 1; i++)
				buttons[i]->displayButton(win);
		}
		else if (status == 2)
		{
			displayCredits(win);
		}
	}
	void hideMenu() {}
	
	std::pair<int,int> menuLogic(sf::RenderWindow& win)
	{
		if (buttons[0]->checkIfButtonPressed(win))
		{
			buttons[0]->setInactive();
			menuChoices.first = true;
			status = 0;
		}
		if (buttons[1]->checkIfButtonPressed(win))
		{
			buttons[1]->setInactive();
			menuChoices.first = true;
			menuChoices.second = false;
			status = 0;
		}
		if (buttons[2]->checkIfButtonPressed(win))
		{
			for (size_t i{ 0 }; i < buttons.size() - 1; i++)
				buttons[i]->setInactive();
			buttons[4]->setActive();
			status = 2;
		}
		if (buttons[3]->checkIfButtonPressed(win))
		{
			buttons[3]->setInactive();
			menuChoices.first = false;
			status = 0;
		}
		if (buttons[4]->checkIfButtonPressed(win))
		{
			buttons[4]->setInactive();
			status = 1;
		}

		if(status == 1)
			for (size_t i{ 0 }; i < buttons.size() - 1; i++)
				buttons[i]->setActive();
	
			return menuChoices;
	}

	bool getStatus() 
	{
		return status;
	}


	void displayCredits(sf::RenderWindow& win)
	{
		creditsText.setCharacterSize(80);
		creditsText.setString(credits[0]);
		creditsText.setPosition(sf::Vector2f(width / 2, 200));
		win.draw(creditsText);

		creditsText.setString(credits[1]);
	//	creditsText.setCharacterSize(80);
		creditsText.setPosition(sf::Vector2f(width / 2, 300));
		win.draw(creditsText);

		creditsText.setCharacterSize(40);
		creditsText.setString(credits[2]);
		creditsText.setPosition(sf::Vector2f(width / 2, 390));
		win.draw(creditsText);

		creditsText.setString(credits[3]);
		creditsText.setPosition(sf::Vector2f(width / 2, 600));
		win.draw(creditsText);

		buttons[4]->displayButton(win);
	}
};


#endif // !MENU
