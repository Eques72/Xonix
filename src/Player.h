#ifndef PLAYER
#define PLAYER

#include <set>
#include "Entity.h"

class Player : public Entity
{
	/**
	* Struktura przechowuj�ca dane potrzebne do zmiany kierunku postaci,
	* przypisywane s� kiedy steruj�cy u�ytkownik zarz�da obrotu postaci
	* Dane wyko�ystane s� przy najbli�szym mo�liwym obrocie
	*/
	struct nextMove
	{
		bool inQueue = false;
		std::pair<int, int> nextVelocity = { 0,0 };
		float nextRotation = 0;
	};

	nextMove nM;
	bool conquestPossible = false;
	bool playerEntered = false;

	//void drop(Map& map, int XY); //wype�nia plamami miejsca puste z kt�rymi maj� stycczno�� przeciwnicy
//	void conquer(Map& map, std::vector<int> positions);

	bool checkPlayerState(int state);

	bool checkCrumbleCollison(Map& map);

	void revivePlayer();

	/**
	* Funkcja ujmuj�ca wszystkie aspekty poruszania si� postaci wywo�uj�ca inne wyspecjalizowane wynkcje
	* oraz obliczaj�ca podstawowe parametry poruszania
	*/
	void move(Map& map) override;

	/**
	* Funkcja zapewniaj�ca �e posta� obr�ci si� w najbli�szym mo�liwym momencie,
	* kiedy centrum b�dzie pokrywa�o si� z centrum pola na mapie
	*/
	void planNextTurn(int x, int y, float degree);
	/**
	* Funkcja sprawdza kolizje z kra�cami mapy, ustawia odpowiednio posta� aby nie wykroczy�a poza granice
	*/
	int checkCollisons(sf::Vector2f pos);

	/**
	* Funkcja zmienia o podane paremetry obecny kierunek postaci okre�lany warto��iami
	* [	0 1	-1]
	*/
	void changeVelocity(float x, float y);

	/**
	* Funkcja obraca Sprite o podany w stopniach k�t liczony zawsze od zwrotu gdy rotacja wynosi domy�ln� warto��
	*/
	void rotate(float angle);

	bool getConquestState();

	friend class GameLogic;
	friend class KeyboardImput;

public:

	/**
	* Konstruktor iniclalizuj�cy startowe parametry postaci oraz tworz�cy dynamiczne obiekty
	*/
	Player(int s);

	std::pair<int, int> getPositionPx();

	/**
	* Funkcja sprawdza nad jakiego typu polem jest centrum postaci,
	* Przyjmuje wska�nik na obiekt Mapy u�ywanej obecnie
	* Wywo�ywana w Player::move() tylko kiedy �rodek wchodzi na nowy obszar(pole)
	* Zwraca okre�lany numerycznie typ pola pod postaci�
	*/
	std::pair<int, int> checkTileBellow(Map& map);
};

#endif // !PLAYER
