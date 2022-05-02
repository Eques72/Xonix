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
		std::pair<int, int> nextVelocity = {0,0};
		float nextRotation = 0;
	};

	class Tail
	{
		Player* head;
		bool playerEntered = false;

	public:
		Tail(Player* p): head(p) {}
		
		bool checkPlayerState(int state) 
		{
			if (playerEntered == 0 && state == Map::EMPTY_TILE)
			{
				playerEntered = 1;
				return 0;
			}
			else if (playerEntered == 1 && state == Map::WALL_TILE)
			{
				playerEntered = 0;
				return 1;
			}
			return 0;
		}
	};

	nextMove nM;
	Tail* tail;
	bool conquestPossible = false;


	void drop(Map* map, int XY); //wype³nia plamami miejsca puste z którymi maj¹ styccznoœæ przeciwnicy





	/**
	* Konstruktor iniclalizuj¹cy startowe parametry postaci oraz tworz¹cy dynamiczne obiekty
	*/
	Player(int s);

	void revivePlayer();

	/**
	* Funkcja ujmuj¹ca wszystkie aspekty poruszania siê postaci wywo³uj¹ca inne wyspecjalizowane wynkcje 
	* oraz obliczaj¹ca podstawowe parametry poruszania
	*/
	void move(Map* map) override;

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
	void changeVelocity(int x, int y);

	/**
	* Funkcja obraca Sprite o podany w stopniach k¹t liczony zawsze od zwrotu gdy rotacja wynosi domyœln¹ wartoœæ
	*/
	void rotate(float angle);

	bool getConquestState();

	void conquer(Map* map, std::vector<int> positions);

	/**
	* Destruktor
	*/
	~Player();


	friend class GameLogic;
	friend class KeyboardImput;

	public:

	std::pair<int, int> getPositionPx();

	/**
	* Funkcja sprawdza nad jakiego typu polem jest centrum postaci,
	* Przyjmuje wskaŸnik na obiekt Mapy u¿ywanej obecnie
	* Wywo³ywana w Player::move() tylko kiedy œrodek wchodzi na nowy obszar(pole)
	* Zwraca okreœlany numerycznie typ pola pod postaci¹
	*/
	std::pair<int, int> checkTileBellow(Map* map);

};

#endif // !PLAYER
