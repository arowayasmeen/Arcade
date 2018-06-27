
#pragma once
#include <list>

using namespace std;

class Block;

class Snake
{
private:
	list<Block> _snake;
	sf::RenderWindow *_app;
	enum direction { UP, RIGHT, DOWN, LEFT };
	int _direction;

public:
	Snake(sf::RenderWindow&);

	void move(int);
	void draw();

	void grow();
	void shrink();

	list<Block> getBlocks();

	int getX();
	int getY();
};