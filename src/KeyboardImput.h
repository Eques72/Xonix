#ifndef KEYBOARD
#define KEYBOARD

#include <memory>
#include <SFML/Graphics.hpp>
#include "Player.h"

class KeyboardImput
{
	std::shared_ptr<Player> player;

public:

	KeyboardImput() {};
	KeyboardImput(std::shared_ptr<Player> p);

	void setPlayer(std::shared_ptr<Player> p);

	void checkKeyboardImput(bool& activatePause);
};
#endif // !KEYBOARD
