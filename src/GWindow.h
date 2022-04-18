#ifndef G_WINDOW
#define G_WINDOW

#include <SFML/Graphics.hpp>

/**
*  Klasa zarz¹dza g³ównym oknem gry z wyko¿ystaniem biblioteki SFML
*/
class GWindow 
{
	const static int width{ 1620 };
	const static int height{ 900 };
	sf::RenderWindow window;

	/**
	* Funkcja ustawia podstawowe parametry okna. 
	* Podstawowo rozdzielczoœæ to 1400x800, liczba klatek to 60.
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

