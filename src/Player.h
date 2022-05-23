#ifndef PLAYER
#define PLAYER

#include <set>
#include "Entity.h"

class Player : public Entity
{
	/**
	* Struktura przechowuj¹ca dane potrzebne do zmiany kierunku postaci,
	* przypisywane s¹ kiedy steruj¹cy u¿ytkownik zarz¹da obrotu postaci
	* Dane wyko¿ystane s¹ przy najbli¿szym mo¿liwym obrocie
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

	//void drop(Map& map, int XY); //wype³nia plamami miejsca puste z którymi maj¹ styccznoœæ przeciwnicy
//	void conquer(Map& map, std::vector<int> positions);

	bool checkPlayerState(int state);

	bool checkCrumbleCollison(Map& map);

	void revivePlayer();

	/**
	* Funkcja ujmuj¹ca wszystkie aspekty poruszania siê postaci wywo³uj¹ca inne wyspecjalizowane wynkcje
	* oraz obliczaj¹ca podstawowe parametry poruszania
	*/
	void move(Map& map) override;

	/**
	* Funkcja zapewniaj¹ca ¿e postaæ obróci siê w najbli¿szym mo¿liwym momencie,
	* kiedy centrum bêdzie pokrywa³o siê z centrum pola na mapie
	*/
	void planNextTurn(int x, int y, float degree);
	/**
	* Funkcja sprawdza kolizje z krañcami mapy, ustawia odpowiednio postaæ aby nie wykroczy³a poza granice
	*/
	int checkCollisons(sf::Vector2f pos);

	/**
	* Funkcja zmienia o podane paremetry obecny kierunek postaci okreœlany wartoœæiami
	* [	0 1	-1]
	*/
	void changeVelocity(float x, float y);

	/**
	* Funkcja obraca Sprite o podany w stopniach k¹t liczony zawsze od zwrotu gdy rotacja wynosi domyœln¹ wartoœæ
	*/
	void rotate(float angle);

	bool getConquestState();

	friend class GameLogic;
	friend class KeyboardImput;

public:

	/**
	* Konstruktor iniclalizuj¹cy startowe parametry postaci oraz tworz¹cy dynamiczne obiekty
	*/
	Player(int s);

	std::pair<int, int> getPositionPx();

	/**
	* Funkcja sprawdza nad jakiego typu polem jest centrum postaci,
	* Przyjmuje wskaŸnik na obiekt Mapy u¿ywanej obecnie
	* Wywo³ywana w Player::move() tylko kiedy œrodek wchodzi na nowy obszar(pole)
	* Zwraca okreœlany numerycznie typ pola pod postaci¹
	*/
	std::pair<int, int> checkTileBellow(Map& map);
};

#endif // !PLAYER
