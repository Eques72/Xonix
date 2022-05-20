#include "GWindow.h"

void GWindow::config()
{
	window.create(sf::VideoMode(width, height), "Pac-xon!", sf::Style::Close);
	window.setPosition(sf::Vector2i(0, 0));
	window.setFramerateLimit(60);

	setGameIcon();
}

void GWindow::setGameIcon()
{
	sf::Image icon;
	icon.loadFromFile("resources/Logo.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

GWindow::GWindow()
{
	config();
}

sf::RenderWindow& GWindow::getWindow() { return window; }


void GWindow::setMenu() 
{
	menu = std::make_unique<Menu>();
}

std::pair<bool, bool> GWindow::displayMenu()
{
	std::pair<int, int> choices;
	while (window.isOpen() && menu->getStatus() != 0)
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		choices = menu->menuLogic(window);

		window.clear();
			menu->displayMenu(window);
		window.display();

	}

	menu.reset();
	return choices;
}

void GWindow::setInfoPanel(int _x, int _y, int _w, int _h) 
{
	iP = std::make_unique<InfoPanel>(_x,_y,_w,_h);
	iP->setNewInfo(0, 0, 0.0, 0.0);
}

void GWindow::displayInfoPanel(int level, int hp, double percent, double percent_needed)
{
	iP->setNewInfo(level, hp, percent, percent_needed);
	iP->drawInfo(this->window);
}


void GWindow::displayDefeatBox()
{
	tB = std::make_unique<TextBox>(width / 2 - 300, height/2 - 300, 600, 600, "You Loose!", "press back to return to menu");
	tB->turnFrame(true);
	tB->displayTextBox(this->window);
	tB->waitForKeyLoop(this->window);

	tB.release();
}

void GWindow::displayPauseBox()
{
	tB = std::make_unique<TextBox>(width / 2 - 200, height / 2 - 200, 400, 400, "Pause", " ");
	tB->turnFrame(false);
	tB->displayTextBox(this->window);
	tB->waitForKeyLoop(this->window);

	tB.release();
}