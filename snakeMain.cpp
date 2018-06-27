

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include <sstream>
#include <SFML/Audio.hpp>
#include "block.h"
#include "snake.h"
#include "fruit.h"
#include "snakeMain.h"

using namespace std;

int snakeMain ::snakef()
{
	// Window
	sf::RenderWindow app(sf::VideoMode(800, 500), "POKE SNEK!", sf::Style::Close);

	app.setFramerateLimit(7);

	//background
	sf::Texture back;
	if (back.loadFromFile("ResourceSnake/back2.png") == -1) {
		return 0;
	}
	sf::RectangleShape background;
	background.setPosition(0, 0);
	background.setSize(sf::Vector2f(800, 500));
	background.setTexture(&back);

	//Font and text
	sf::Font font;
	if (font.loadFromFile("ResourceSnake/a.ttf") == 0) {
		cout << "loading error" << endl;
	}

	sf::Text title;
	title.setFont(font);
	title.setCharacterSize(30);
	title.setPosition(300, 250);

	sf::Text title2;
	title2.setFont(font);
	title2.setCharacterSize(30);
	title2.setPosition(280, 200);
	title2.setString("GAME OVER");

	sf::Text title3;
	title3.setFont(font);
	title3.setCharacterSize(25);
	title3.setPosition(210, 400);
	title3.setString("press any key to exit");

	//// The snake - pickachu heads
	Snake snake(app);//initialises first two pickachu heads

	int score = 0;//initial score set to 0

				  // Building up the entire snake - trail of pickachu heads
	list<Block> blocks;// A list containing the position of each pickachu head
	list<Block>::iterator it;

	// Direction of the snake
	enum direction { UP, RIGHT, DOWN, LEFT };
	int direction = RIGHT;


	//// The fruit - Pokeball
	Fruit fruit(app);

	// Tells if we need to respawn pokeball
	bool mustSpawnFruit = true;

	// Coords of the fruit
	int fruitX;
	int fruitY;

	//Sound
	sf::SoundBuffer startGame;
	if (startGame.loadFromFile("ResourceSnake/start.wav") == 0)cout << "error" << endl;
	sf::Sound start;
	start.setBuffer(startGame);
	start.play();

	sf::SoundBuffer pickPokeball;
	if (pickPokeball.loadFromFile("ResourceSnake/Pickup_pokeball.wav") == 0)cout << "error" << endl;
	sf::Sound pickup;
	pickup.setBuffer(pickPokeball);


	sf::SoundBuffer endGame;
	if (endGame.loadFromFile("ResourceSnake/dead.wav") == 0)cout << "error" << endl;
	sf::Sound end;
	end.setBuffer(endGame);


	while (app.isOpen())
	{
		app.clear();


		sf::Event Event;

		while (app.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				app.close();
			}

			// Determine the direction of the snake
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right))
			{
				direction = RIGHT;
			}
			else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left))
			{
				direction = LEFT;
			}
			else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
			{
				direction = UP;
			}
			else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
			{
				direction = DOWN;
			}
		}
		app.draw(background);


		//Spawn pokeball if necessary
		if (mustSpawnFruit)
		{
			bool safe = true;

			// We make sure that it doesn't spawn on the snake
			do
			{
				fruitX = (rand() % 20) * 25;
				fruitY = (rand() % 20) * 25;

				blocks = snake.getBlocks();

				for (it = blocks.begin(); it != blocks.end(); it++)
				{
					if (it->getX() == fruitX && it->getY() == fruitY)
					{
						safe = false;
						break;
					}
					else
					{
						safe = true;
					}
				}
			} while (safe != true);

			mustSpawnFruit = false;
		}

		fruit.spawn(fruitX, fruitY);//Draws pokeball on screen

		snake.move(direction);//sets new position for snake
		snake.draw();

		//checks bounds
		if (snake.getX() >= 800 || snake.getX() < 0 || snake.getY() >= 500 || snake.getY() < 0)
		{
			bool play = true;

			end.play();//sound

			while (play) {


				sf::Event event;
				while (app.pollEvent(event)) {


					if (event.type == sf::Event::Closed)
					{
						play = false;
						app.close();
					}
					if ((event.type == sf::Event::KeyPressed))
					{
						play = false;
						app.close();
					}


				}

				//printing score									
				string scr;
				ostringstream ss;
				ss << "SCORE: ";
				ss << score;
				scr = ss.str();
				title.setString(scr);


				app.draw(title);
				app.draw(title2);
				app.draw(title3);
				app.display();

			}


		}

		//Check to see if it hits pokeball
		if (snake.getX() == fruit.getX() && snake.getY() == fruit.getY())
		{

			mustSpawnFruit = true;
			score++;

			snake.grow();

			pickup.play();


		}

		//Check to see if snake hits itself
		blocks = snake.getBlocks();
		it = blocks.begin();

		it++; // not required to check for first Pikachu head

		for (it; it != blocks.end(); it++)
		{
			if (it->getX() == snake.getX() && it->getY() == snake.getY())
			{
				bool play = true;
				end.play();
				while (play) {


					sf::Event event;
					while (app.pollEvent(event)) {


						if (event.type == sf::Event::Closed)
						{
							play = false;
							app.close();
						}
						if ((event.type == sf::Event::KeyPressed))
						{
							play = false;
							app.close();
						}


					}

					//printing score
					string scr;
					ostringstream ss;
					ss << "SCORE: ";
					ss << score;
					scr = ss.str();
					title.setString(scr);
					title.setString(scr);

					app.draw(title);
					app.draw(title2);
					app.draw(title3);
					app.display();

				}

			}
		}


		app.display();
	}

	return 0;
}