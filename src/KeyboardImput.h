#ifndef KEYBOARD
#define KEYBOARD

#include <memory>
#include <SFML/Graphics.hpp>
#include "Player.h"

/// <summary>
/// Manages events related do pressing keyboard's buttons
/// </summary>
class KeyboardImput
{
	std::shared_ptr<Player> player;

public:

	/// <summary>
	/// Default constructor
	/// </summary>
	KeyboardImput() {};

	/// <summary>
	/// Constructor which takes pointer to Player, 
	/// allows to pass kayboard imput to be passed futher 
	/// </summary>
	KeyboardImput(std::shared_ptr<Player> p);

	/// <summary>
	/// Sets a pointer to a player object 
	/// </summary>
	void setPlayer(std::shared_ptr<Player> p);

	/// <summary>
	/// Method check selected buttons states and process events
	/// </summary>
	/// <param name="activatePause">Boolean value changed if "P" or "ESC" is pressed</param>
 	void checkKeyboardImput(bool& activatePause);
};
#endif // !KEYBOARD
