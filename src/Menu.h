#ifndef MENU
#define MENU

#include <array>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "FileManager.h"
#include <chrono>

class Menu 
{
	const static int width{ 1620 };
	const static int height{ 1100 };
	const std::array<std::string, 4> credits = { "Game created by: " ,"Adran Zareba" ,"as a project for Computer Programming IV lecture" ,"See more at: https://github.com/Eques72" };
	int status = 1; //1 - active, schow buttons, 2 - active, show credits, 0 - inactive
	std::array<bool, 3> menuChoices{ false,false,false }; //(active = 1, inactive = 0, exit game = false)
	bool demandedCredits = false;

	sf::Image backgroundImg;
	sf::Texture backgroundTx;
	sf::Sprite backgroundSprite;
	std::array<std::unique_ptr<Button>,5> buttons;

	sf::Font font;
	sf::Text menuText;
	sf::Text creditsText;

	static constexpr std::chrono::milliseconds holdTime{ 200 };
	std::chrono::time_point<std::chrono::steady_clock> timeStamp;

public:

	Menu();

	void displayMenu(sf::RenderWindow& win);
	
	std::array<bool, 3> menuLogic(sf::RenderWindow& win);

	void displayCredits(sf::RenderWindow& win);

	void checkForDemand(bool creditsNeeded);

	void waitFunction();

	void setUpText();
	void initializeButtons();

	inline bool getStatus() 
	{
		return status;
	}
};


#endif // !MENU
