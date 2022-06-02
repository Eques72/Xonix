#ifndef PLAYER
#define PLAYER

#include <set>
#include "Entity.h"

/// <summary>
/// Class represents a player character
/// </summary>
class Player : public Entity
{
private:
	/// <summary>
	/// Structure that is used to hold data needed for change of entity direction
	/// </summary>
	struct nextMove
	{
		bool inQueue = false;
		std::pair<int, int> nextVelocity = { 0,0 };
		float nextRotation = 0;
	};

	nextMove nM;
	bool conquestPossible = false;
	bool playerEntered = false;

	/// <summary>
	/// Check if player is currently on empty tile or wall tile and matches its state accordingly
	/// </summary>
	/// <param name="state">State of tile bellow player</param>
	/// <returns>Retruns true if player has exited empty tile and entered wall tile</returns>
	bool checkPlayerState(int state);

	/// <summary>
	/// Checks if player is on any crumbling tile;
	/// </summary>
	/// <param name="map">Reference to active map</param>
	/// <returns>Returns true if it touches a crumbling tile</returns>
	bool checkCrumbleCollison(Map& map);

	/// <summary>
	/// Resets player position to starting position
	/// </summary>
	void revivePlayer();
	
	/// <summary>
	/// Method handles all aspect of character movement
	/// </summary>
	/// <param name="map">Reference to active map</param>
	void move(Map& map) override;

	/// <summary>
	/// Method sets up nextMove struture to hold all data needed for change of direction
	/// </summary>
	/// <param name="degree">Degrees to turn</param>
	void planNextTurn(int x, int y, float degree);
	
	/// <summary>
	/// Method check collisions with map borders and prevents entity from leaving
	/// </summary>
	/// <param name="pos">Entity position (coordinates)</param>
	void checkCollisons(sf::Vector2f pos);

	/// <summary>
	/// Changes velocity of the player
	/// </summary>
	/// <param name="x">new x velocity</param>
	/// <param name="y">new y velocity</param>
	void changeVelocity(float x, float y);

	/// <summary>
	/// Rotates player's sprite by certain degrees
	/// </summary>
	/// <param name="angle">Angle in degrees</param>
	void rotate(float angle);

	/// <summary>
	/// </summary>
	/// <returns>Returns conquestPossible variable</returns>
	bool getConquestState();

	friend class GameLogic;
	friend class KeyboardImput;

public:

	Player(int s);

	/// <summary>
	/// </summary>
	/// <returns>Returns players position</returns>
	std::pair<int, int> getPositionPx();


	/// <summary>
	/// Method checks what tile type is bellow player sprite
	/// </summary>
	/// <param name="map">Reference to active map</param>
	/// <returns>Returns index of the tile and the tile type</returns>
	std::pair<int, int> checkTileBellow(Map& map);
};

#endif // !PLAYER
