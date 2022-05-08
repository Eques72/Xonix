#ifndef G_WINDOW
#define G_WINDOW

#include <SFML/Graphics.hpp>

/**
*  Klasa zarządza głównym oknem gry z wykożystaniem biblioteki SFML
*/
class GWindow
{
	const static int width{ 1620 };
	const static int height{ 900 };
	sf::RenderWindow window;

	/**
	* Funkcja ustawia podstawowe parametry okna.
	* Podstawowo rozdzielczość to 1400x800, liczba klatek to 60.
	*/
	void config();

	void setGameIcon();

public:

	/*
	* Konstruktor klasy GameWindow.
	*/
	GWindow();

	sf::RenderWindow& getWindow();
};

#endif //G_WINDOW

