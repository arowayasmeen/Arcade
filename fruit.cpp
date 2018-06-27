
#include <SFML/Graphics.hpp>
#include <iostream>

#include "fruit.h"

using namespace std;

Fruit::Fruit(sf::RenderWindow &App)
{
	_app = &App;
}

void Fruit::spawn(float x, float y)
{

	sf::Texture image1;
	if (image1.loadFromFile("ResourceSnake/ball2.png") == -1) {
		cout << "loading error" << endl;

	}

	//Structure for Pokeball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(25, 25));
	ball.setPosition(x, y);
	ball.setFillColor(sf::Color::White);
	ball.setTexture(&image1);

	_x = x;
	_y = y;

	_app->draw(ball);
}

float Fruit::getX()
{
	return _x;
}

float Fruit::getY()
{
	return _y;
}