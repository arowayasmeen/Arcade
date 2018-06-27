#pragma once


class Fruit
{
private:
	sf::RenderWindow *_app;
	float _x;
	float _y;
public:
	Fruit(sf::RenderWindow&);

	void spawn(float, float);

	float getX();
	float getY();
};
