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
