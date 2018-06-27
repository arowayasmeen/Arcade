
#include <SFML/Graphics.hpp>
#include <iostream>
#include "snake.h"
#include "block.h"

using namespace std;

Snake::Snake(sf::RenderWindow &App)
{
	_app = &App;
	_direction = RIGHT;//initial direction of movement

					   // Draws the initial snake
	_snake.push_front(Block(25, 0));//Position of first pickachu head
	_snake.push_front(Block(50, 0));//position of second pickachu head 
}

void Snake::move(int newDirection)
{
	shrink();

	if (newDirection == UP)
	{
		if (_direction != DOWN)
		{
			_snake.push_front(Block(_snake.front().getX(), _snake.front().getY() - 25));
			_direction = UP;
		}
		else
		{
			_snake.push_front(Block(_snake.front().getX(), _snake.front().getY() + 25));
		}
	}

	else if (newDirection == RIGHT)
	{
		if (_direction != LEFT)
		{
			_snake.push_front(Block(_snake.front().getX() + 25, _snake.front().getY()));
			_direction = RIGHT;
		}
		else
		{
			_snake.push_front(Block(_snake.front().getX() - 25, _snake.front().getY()));
		}
	}

	else if (newDirection == DOWN)
	{
		if (_direction != UP)
		{
			_snake.push_front(Block(_snake.front().getX(), _snake.front().getY() + 25));
			_direction = DOWN;
		}
		else
		{
			_snake.push_front(Block(_snake.front().getX(), _snake.front().getY() - 25));
		}

	}

	else if (newDirection == LEFT)
	{
		if (_direction != RIGHT)
		{
			_snake.push_front(Block(_snake.front().getX() - 25, _snake.front().getY()));
			_direction = LEFT;
		}
		else
		{
			_snake.push_front(Block(_snake.front().getX() + 25, _snake.front().getY()));
		}
	}
}

void Snake::draw()
{
	for (list<Block>::iterator it = _snake.begin(); it != _snake.end(); it++)
	{
		float x = it->getX();
		float y = it->getY();


		sf::Texture image1;
		if (image1.loadFromFile("ResourceSnake/Pikachu.png") == -1) {
			cout << "loading error" << endl;

		}

		sf::RectangleShape block;
		block.setSize(sf::Vector2f(30, 30));
		block.setPosition(x, y);
		block.setFillColor(sf::Color::White);
		block.setTexture(&image1);





		_app->draw(block);
	}
}

void Snake::grow()
{
	_snake.push_back(Block(_snake.back().getX(), _snake.back().getY()));
}

void Snake::shrink()
{
	_snake.pop_back();
}

list<Block> Snake::getBlocks()
{
	return _snake;
}

int Snake::getX()
{
	return _snake.front().getX();
}

int Snake::getY()
{
	return _snake.front().getY();
}