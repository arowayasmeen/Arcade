#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <SFML/Audio.hpp>
#include "ttt.h"
using namespace std;

char matrix[3][3] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char p1 = 'X';
char p2 = 'O';


char Win()
{
	//first player
	if (matrix[0][0] == 'X' && matrix[0][1] == 'X' && matrix[0][2] == 'X')
		return 'X';
	if (matrix[1][0] == 'X' && matrix[1][1] == 'X' && matrix[1][2] == 'X')
		return 'X';
	if (matrix[2][0] == 'X' && matrix[2][1] == 'X' && matrix[2][2] == 'X')
		return 'X';

	if (matrix[0][0] == 'X' && matrix[1][0] == 'X' && matrix[2][0] == 'X')
		return 'X';
	if (matrix[0][1] == 'X' && matrix[1][1] == 'X' && matrix[2][1] == 'X')
		return 'X';
	if (matrix[0][2] == 'X' && matrix[1][2] == 'X' && matrix[2][2] == 'X')
		return 'X';

	if (matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X')
		return 'X';
	if (matrix[2][0] == 'X' && matrix[1][1] == 'X' && matrix[0][2] == 'X')
		return 'X';

	//second player
	if (matrix[0][0] == 'O' && matrix[0][1] == 'O' && matrix[0][2] == 'O')
		return 'O';
	if (matrix[1][0] == 'O' && matrix[1][1] == 'O' && matrix[1][2] == 'O')
		return 'O';
	if (matrix[2][0] == 'O' && matrix[2][1] == 'O' && matrix[2][2] == 'O')
		return 'O';

	if (matrix[0][0] == 'O' && matrix[1][0] == 'O' && matrix[2][0] == 'O')
		return 'O';
	if (matrix[0][1] == 'O' && matrix[1][1] == 'O' && matrix[2][1] == 'O')
		return 'O';
	if (matrix[0][2] == 'O' && matrix[1][2] == 'O' && matrix[2][2] == 'O')
		return 'O';

	if (matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O')
		return 'O';
	if (matrix[2][0] == 'O' && matrix[1][1] == 'O' && matrix[0][2] == 'O')
		return 'O';

	return '/';
}


int ttt::tttf() {


	sf::RenderWindow window(sf::VideoMode(400, 400), "TIC TAC TOE");//create window
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	memset(matrix, 0, sizeof(matrix[0][0]) * 3 * 3);

	sf::Event event;

	//font
	sf::Texture text1;
	if (text1.loadFromFile("cross.png") == 0) {
		return 0;
	}
	sf::Texture text2;
	if (text2.loadFromFile("full-moon.png") == 0) {
		return 0;
	}
	sf::Font font1;
	if (font1.loadFromFile("a.ttf") == 0) {
		return 0;
	}
	sf::SoundBuffer hitb;
	if (hitb.loadFromFile("hit.wav") == 0) {
		return 0;
	}
	sf::Sound hit;
	hit.setBuffer(hitb);

	sf::Text t;
	t.setFont(font1);
	t.setCharacterSize(30);
	t.setFillColor(sf::Color::White);
	t.setPosition(50, 20);
	t.setString("TIC TAC TOE");

	sf::Text play1;
	play1.setFont(font1);
	play1.setCharacterSize(30);
	play1.setFillColor(sf::Color::White);
	play1.setPosition(40, 300);
	play1.setString("Player 1 Wins!");

	sf::Text play2;
	play2.setFont(font1);
	play2.setCharacterSize(30);
	play2.setFillColor(sf::Color::White);
	play2.setPosition(40, 300);
	play2.setString("Player 2 Wins!");

	sf::Text play3;
	play3.setFont(font1);
	play3.setCharacterSize(30);
	play3.setFillColor(sf::Color::White);
	play3.setPosition(150, 300);
	play3.setString("Draw!");





	//states
	bool play = true;
	bool player1 = true;
	bool player2 = false;
	bool flag1 = 0;
	bool flag2 = 0;
	bool ok1 = false;
	bool ok2 = false;
	bool ok3 = false;
	bool ok4 = false;
	bool ok5 = false;
	bool ok6 = false;
	bool ok7 = false;
	bool ok8 = false;
	bool ok9 = false;





	//Variables
	int cnt = 0;


	////Shape
	//background


	//Pad1
	sf::RectangleShape tile1;
	tile1.setSize(sf::Vector2f(50, 50));
	tile1.setPosition(60, 100);
	tile1.setFillColor(sf::Color::White);
	//background.setTexture(&texBackground);

	//pad2
	sf::RectangleShape tile2;
	tile2.setSize(sf::Vector2f(50, 50));
	tile2.setPosition(175, 100);
	tile2.setFillColor(sf::Color::White);

	sf::RectangleShape tile3;
	tile3.setSize(sf::Vector2f(50, 50));
	tile3.setPosition(290, 100);
	tile3.setFillColor(sf::Color::White);

	sf::RectangleShape tile4;
	tile4.setSize(sf::Vector2f(50, 50));
	tile4.setPosition(60, 165);
	tile4.setFillColor(sf::Color::White);

	sf::RectangleShape tile5;
	tile5.setSize(sf::Vector2f(50, 50));
	tile5.setPosition(175, 165);
	tile5.setFillColor(sf::Color::White);

	sf::RectangleShape tile6;
	tile6.setSize(sf::Vector2f(50, 50));
	tile6.setPosition(290, 165);
	tile6.setFillColor(sf::Color::White);

	sf::RectangleShape tile7;
	tile7.setSize(sf::Vector2f(50, 50));
	tile7.setPosition(60, 230);
	tile7.setFillColor(sf::Color::White);

	sf::RectangleShape tile8;
	tile8.setSize(sf::Vector2f(50, 50));
	tile8.setPosition(175, 230);
	tile8.setFillColor(sf::Color::White);

	sf::RectangleShape tile9;
	tile9.setSize(sf::Vector2f(50, 50));
	tile9.setPosition(290, 230);
	tile9.setFillColor(sf::Color::White);






	//game loop
	while (play) {

		//events




		//events stored in queue
		while (window.pollEvent(event)) {


			//cross to close window
			if (event.type == sf::Event::Closed) {

				play = false;
				return 0;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
				if (!ok1) {
					if (player1) {
						cnt++;
						matrix[0][0] = p1;
						flag1 = 1;
						flag2 = 0;
						tile1.setTexture(&text1);
						hit.play();
					}
					else if (player2) {
						cnt++;

						matrix[0][0] = p2;
						flag2 = 1;
						flag1 = 0;
						tile1.setTexture(&text2);
						hit.play();
					}
					ok1 = true;

				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
				if (!ok2) {

					if (player1) {
						cnt++;
						matrix[0][1] = p1;
						flag1 = 1;
						flag2 = 0;
						tile2.setTexture(&text1);
						hit.play();
					}
					else if (player2) {
						cnt++;
						matrix[0][1] = p2;
						flag2 = 1;
						flag1 = 0;
						tile2.setTexture(&text2);
						hit.play();

					}ok2 = true;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
				if (!ok3) {
					if (player1) {
						cnt++;
						matrix[0][2] = p1;
						flag1 = 1;
						flag2 = 0;
						tile3.setTexture(&text1);
						hit.play();
					}
					else if (player2) {
						cnt++;
						matrix[0][2] = p2;
						flag2 = 1;
						flag1 = 0;
						tile3.setTexture(&text2);
						hit.play();
					}
					ok3 = true;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4) {
				if (!ok4) {
					if (player1) {
						cnt++;
						matrix[1][0] = p1;
						flag1 = 1;
						flag2 = 0;
						tile4.setTexture(&text1);
						hit.play();
					}
					else if (player2) {
						cnt++;
						matrix[1][0] = p2;
						flag2 = 1;
						flag1 = 0;
						tile4.setTexture(&text2);
						hit.play();
					}
					ok4 = true;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5) {
				if (!ok5) {
					if (player1) {
						cnt++;
						matrix[1][1] = p1;
						flag1 = 1;
						flag2 = 0;
						tile5.setTexture(&text1);
						hit.play();
					}
					else if (player2) {
						cnt++;
						matrix[1][1] = p2;
						flag2 = 1;
						flag1 = 0;
						tile5.setTexture(&text2);
						hit.play();
					}
					ok5 = true;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) {
				if (!ok6) {
					if (player1) {
						cnt++;
						matrix[1][2] = p1;
						flag1 = 1;
						flag2 = 0;
						tile6.setTexture(&text1);
						hit.play();
					}
					else if (player2) {
						cnt++;
						matrix[1][2] = p2;
						flag2 = 1;
						flag1 = 0;
						tile6.setTexture(&text2);
						hit.play();
					}
					ok6 = true;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num7) {
				if (!ok7) {
					if (player1) {
						cnt++;
						matrix[2][0] = p1;
						flag1 = 1;
						flag2 = 0;
						tile7.setTexture(&text1);
						hit.play();
					}
					else if (player2) {
						cnt++;
						matrix[2][0] = p2;
						flag2 = 1;
						flag1 = 0;
						tile7.setTexture(&text2);
						hit.play();
					}
					ok7 = true;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num8) {
				if (!ok8) {
					if (player1) {
						cnt++;
						matrix[2][1] = p1;
						flag1 = 1;
						flag2 = 0;
						tile8.setTexture(&text1);
						hit.play();
					}
					else if (player2) {
						cnt++;
						matrix[2][1] = p2;
						flag2 = 1;
						flag1 = 0;
						tile8.setTexture(&text2);
						hit.play();
					}
					ok8 = true;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num9) {
				if (!ok9) {
					if (player1) {
						cnt++;
						matrix[2][2] = p1;
						flag1 = 1;
						flag2 = 0;
						tile9.setTexture(&text1);
						hit.play();
					}
					else if (player2) {
						cnt++;
						matrix[2][2] = p2;
						flag2 = 1;
						flag1 = 0;
						tile9.setTexture(&text2);
						hit.play();
					}
					ok9 = true;
				}
			}


			if (flag1 && !flag2) {
				player2 = true;
				player1 = false;

			}
			else if (!flag1 && !flag1) {
				player1 = true;
				player2 = false;
			}




		}

		//////logic
		char w = Win();
		if (w == 'X') {

			play = false;
			bool splay = true;

			while (splay) {

				sf::Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed)
					{
						splay = false;
						window.close();
						return 0;
					}
					if ((ev.type == sf::Event::KeyPressed))
					{
						splay = false;
						window.close();
						return 0;
					}
				}
				window.clear();
				window.draw(tile1);
				window.draw(tile2);
				window.draw(tile3);
				window.draw(tile4);
				window.draw(tile5);
				window.draw(tile6);
				window.draw(tile7);
				window.draw(tile8);
				window.draw(tile9);
				window.draw(play1);
				window.display();


			}
		}

		if (w == 'O') {

			play = false;
			bool splay = true;

			while (splay) {

				sf::Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed)
					{
						splay = false;
						window.close();
						return 0;
					}
					if ((ev.type == sf::Event::KeyPressed))
					{
						splay = false;
						window.close();
						return 0;
					}
				}
				window.clear();
				window.draw(tile1);
				window.draw(tile2);
				window.draw(tile3);
				window.draw(tile4);
				window.draw(tile5);
				window.draw(tile6);
				window.draw(tile7);
				window.draw(tile8);
				window.draw(tile9);
				window.draw(play2);
				window.display();
			}
		}

		else if (w == '/' && cnt == 9) {

			play = false;
			bool splay = true;

			while (splay) {

				sf::Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed)
					{
						splay = false;
						window.close();
						return 0;
					}
					if ((ev.type == sf::Event::KeyPressed))
					{
						splay = false;
						window.close();
						return 0;
					}
				}
				window.clear();
				window.draw(tile1);
				window.draw(tile2);
				window.draw(tile3);
				window.draw(tile4);
				window.draw(tile5);
				window.draw(tile6);
				window.draw(tile7);
				window.draw(tile8);
				window.draw(tile9);
				window.draw(play3);
				window.display();
			}
		}


		window.clear();
		window.draw(t);
		window.draw(tile1);
		window.draw(tile2);
		window.draw(tile3);
		window.draw(tile4);
		window.draw(tile5);
		window.draw(tile6);
		window.draw(tile7);
		window.draw(tile8);
		window.draw(tile9);
		window.display();



	}

	return 0;

}



