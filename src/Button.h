#ifndef BUT
#define BUT

#include <memory>
#include <SFML/Graphics.hpp>

class Button
{
	int x{ 0 };
	int y{ 0 };
	int width{ 220 };
	int height{ 110 };
	std::string label{"BUTTON"};
//	std::shared_ptr<sf::RenderWindow> parentWindow;
	bool active = true;
	sf::Color color = sf::Color::White;

	sf::Sprite bodyButton;
	sf::Text buttonText;
	sf::Texture tx;
	sf::Font f;
public:
//	Button(int _x, int _y, int _w, int _h, sf::Color c, std::string _label, std::shared_ptr<sf::RenderWindow> _parentWindow) 
	Button(int _x, int _y, int _w, int _h, sf::Color c, std::string _label)
		: x(_x), y(_y), width(_w), height(_h), color(c), label(_label) 
	{
		tx.loadFromFile("resources/button.png");

		bodyButton.setColor(color);
		bodyButton.setPosition(sf::Vector2f(x, y));
		bodyButton.setTexture(tx);

		f.loadFromFile("resources/DIGIB.TTF");
		buttonText.setFont(f);
		buttonText.setString(label);
		buttonText.setCharacterSize(55);
		buttonText.setFillColor(sf::Color(169, 179, 186));
	//	buttonText.setOutlineColor(sf::Color(169, 179, 186));
		buttonText.setStyle(sf::Text::Bold);

		//center text
		sf::FloatRect textRect = buttonText.getLocalBounds();
		buttonText.setOrigin(textRect.width / 2, textRect.height / 2);
		buttonText.setPosition(sf::Vector2f(x+width/2, y + (3*height/8)));
	};

	void displayButton(sf::RenderWindow& win) 
	{
		win.draw(bodyButton);
		win.draw(buttonText);
	}
	
	bool checkIfButtonPressed(sf::RenderWindow& win)
	{
		if (active && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mPos = sf::Mouse::getPosition(win);
				//AABB
				if (mPos.x >= x && mPos.x <= x + width && mPos.y >= y && mPos.y <= y + height)
					return true;
		}
		return false;
	}

	inline void setActive() 
	{
		active = true;
	}

    inline void setInactive() 
	{
		active = false;
	}
};


#endif // !BUT
