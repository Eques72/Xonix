#ifndef G_WINDOW
#define G_WINDOW

#include <memory>
#include <SFML/Graphics.hpp>
#include "InfoPanel.h"
#include "Menu.h"
#include "TextBox.h"

/**
*  Klasa zarz¹dza g³ównym oknem gry z wyko¿ystaniem biblioteki SFML
*/
class GWindow
{
	sf::RenderWindow window;

	std::unique_ptr<Menu> menu;
	std::unique_ptr<InfoPanel> iP;
	std::unique_ptr<TextBox> tB;

	sf::Font font;
	sf::Text Text;
	

	/**
	* Funkcja ustawia podstawowe parametry okna.
	* Podstawowo rozdzielczoœæ to 1400x800, liczba klatek to 60.
	*/
	void config();

	void setGameIcon();

public:
	const static int width{ 1620 };
	const static int height{ 1100 }; //{ 900 };
	/*
	* Konstruktor klasy GameWindow.
	*/
	GWindow();

	void setMenu();
	std::pair<bool,bool> displayMenu();

	sf::RenderWindow& getWindow();

	void displayDefeatBox();
	void displayPauseBox();

	void setInfoPanel(int _x, int _y, int _w, int _h);
	void displayInfoPanel(int level, int hp, double percent, double percent_needed);

};

#endif //G_WINDOW

