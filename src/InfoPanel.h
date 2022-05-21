#ifndef INFO_P
#define INFO_P

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "FileManager.h"


class InfoPanel
{
	std::string prefix_levels{"Level: "};
	std::string prefix_hp{ "Lives left: " };
	std::string prefix_completion{ "Level completion: " };

	std::string s_levels;
	std::string s_hp;
	std::string s_completion;

	sf::Text tLev;
	sf::Text tHp;
	sf::Text tComp;
	sf::Font font;

	int x;
	int y;
	int width;
	int height;

	void setUpText(sf::Text& t, int offset_x);
	void setUpFont(sf::Font& f);

public:

	InfoPanel(int _x, int _y, int _w, int _h);

	void setNewInfo(int level, int hp, double percent, double percent_needed);

	void drawInfo(sf::RenderWindow& win);

};

#endif //INFO_P

