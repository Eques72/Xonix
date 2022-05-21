#ifndef KEYBOARD
#define KEYBOARD

#include <SFML/Graphics.hpp>
#include "Player.h"

class KeyboardImput
{
	Player* player = nullptr;

public:

	KeyboardImput() {};
	KeyboardImput(Player* p);

	void setPlayer(Player* p);

	void checkKeyboardImput(bool& activatePause);
};
#endif // !KEYBOARD
