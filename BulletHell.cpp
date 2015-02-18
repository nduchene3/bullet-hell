// BulletHell.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int main()
{

	//sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!", sf::Style::Titlebar | sf::Style::Close);

	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	//while (window.isOpen())
	//{
	//sf::Event event;
	//while (window.pollEvent(event))
	//{
	//if (event.type == sf::Event::Closed)
	//window.close();
	//}

	//window.clear();
	//window.draw(shape);
	//window.display();
	//}

	Game::Start();

	return 0;
}

