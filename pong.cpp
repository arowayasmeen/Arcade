#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <SFML/Audio.hpp>
#include "pong.h"


using namespace std;

int pong::pongf() {

	sf::RenderWindow window(sf::VideoMode(1000, 600), "POKE PONG!");//create window
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Event event;

	//font
	sf::Font font;
	if (font.loadFromFile("Resources/a.ttf") == 0) {
		return 0;
	}
	sf::Font font2;
	if (font2.loadFromFile("Resources/pokefont.ttf") == 0) {
		return 0;
	}


	sf::Text score;
	score.setFont(font2);
	score.setCharacterSize(30);
	score.setFillColor(sf::Color::Black);
	score.setPosition(450, 15);
	score.setString("0 : 0");

	sf::Text player1;
	player1.setFont(font2);
	player1.setCharacterSize(50);
	player1.setFillColor(sf::Color::Black);
	player1.setPosition(350, 250);
	player1.setString("Player 1 Wins!");

	sf::Text player2;
	player2.setFont(font2);
	player2.setCharacterSize(50);
	player2.setFillColor(sf::Color::Black);
	player2.setPosition(300, 250);
	player2.setString("Computer Wins!");

	sf::Text esc;
	esc.setFont(font);
	esc.setCharacterSize(30);
	esc.setFillColor(sf::Color::Black);
	esc.setPosition(260, 350);
	esc.setString("press any key to exit");

	//images
	sf::Texture texBall;
	sf::Texture texBackground;
	if (texBall.loadFromFile("Resources/ball2.png") == 0)return 0;
	if (texBackground.loadFromFile("Resources/poke2.png") == 0)return 0;


	//sounds
	sf::SoundBuffer hitBuff;
	if (hitBuff.loadFromFile("Resources/hit.wav") == 0)return 0;
	sf::Sound hit;
	hit.setBuffer(hitBuff);



	//states
	bool play = true;
	bool up = false;
	bool down = false;


	//Variables
	int yVelocityPad1 = 0;
	int yVelocityBall = -6;
	int xVelocityBall = -6;
	int yVelocityPad2 = 0;
	int pad1Score = 0;
	int pad2Score = 0;


	////Shape
	//background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(1000, 600));
	background.setPosition(0, 0);
	background.setTexture(&texBackground);

	//Pad1
	sf::RectangleShape pad1;
	pad1.setSize(sf::Vector2f(20, 120));
	pad1.setPosition(30, 200);
	pad1.setFillColor(sf::Color::Black);
	//background.setTexture(&texBackground);

	//pad2
	sf::RectangleShape pad2;
	pad2.setSize(sf::Vector2f(20, 120));
	pad2.setPosition(950, 200);
	pad2.setFillColor(sf::Color::Black);

	//ball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(30, 30));
	ball.setPosition(500, 300);
	ball.setTexture(&texBall);





	//game loop
	while (play) {

		//events
		//sf::Event event;



		//events stored in queue
		while (window.pollEvent(event)) {


			//cross to close window
			if (event.type == sf::Event::Closed) {

				play = false;
			}

			//KeyPressed
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				up = true;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
				down = true;

			}

			//KeyReleased
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
				up = false;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
				down = false;
			}


		}

		//////logic

		////pad1
		if (up)yVelocityPad1 = -7;
		if (down)yVelocityPad1 = 7;
		if (up && down)yVelocityPad1 = 0;
		if (!up && !down)yVelocityPad1 = 0;

		//move
		pad1.move(0, yVelocityPad1);

		//check bounds
		if (pad1.getPosition().y < 0)pad1.setPosition(30, 0);
		if (pad1.getPosition().y > 480)pad1.setPosition(30, 480);


		////ball
		//move
		ball.move(xVelocityBall, yVelocityBall);

		//check bounds
		if (ball.getPosition().y < 0)yVelocityBall = -yVelocityBall;
		if (ball.getPosition().y > 570)yVelocityBall = -yVelocityBall;
		if (ball.getPosition().x < -1) {
			pad2Score++;
			ball.setPosition(500, 300);
		}
		if (ball.getPosition().x > 1000) {
			pad1Score++;
			ball.setPosition(500, 300);
		}

		////pad2
		if (ball.getPosition().y < pad2.getPosition().y)yVelocityPad2 = -6;
		if (ball.getPosition().y > pad2.getPosition().y)yVelocityPad2 = 6;

		pad2.move(0, yVelocityPad2);
		if (pad2.getPosition().y < 0)pad2.setPosition(950, 0);
		if (pad2.getPosition().y > 480)pad2.setPosition(950, 480);

		//collision for pad1
		if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds()) == true) {
			hit.play();
			//ball.setPosition(pad1.getPosition().x + 20, ball.getPosition().y);
			//dsdh bbv cout << ball.getPosition().x << endl;
			if (ball.getPosition().y < pad1.getPosition().y && ball.getPosition().x < 44)yVelocityBall = -yVelocityBall;
			else if (ball.getPosition().y + 30 > pad1.getPosition().y + 120 && ball.getPosition().x < 44)yVelocityBall = -yVelocityBall;
			else {
				xVelocityBall = -xVelocityBall;
				pad1Score++;
			}

		}

		//collison for pad2
		if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds()) == true) {

			ball.setPosition(pad2.getPosition().x - 17 * 2, ball.getPosition().y);
			xVelocityBall = -xVelocityBall;
			hit.play();
			pad2Score++;

		}

		if (pad1Score == 10 & pad2Score != 10) {

			bool play = true;

			while (play) {

				sf::Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed)
					{
						play = false;
						window.close();
						return 0;
					}
					if ((ev.type == sf::Event::KeyPressed))
					{
						play = false;
						window.close();
						return 0;
					}
				}
				window.clear();
				window.draw(background);
				window.draw(pad1);
				window.draw(pad2);
				window.draw(ball);

				//score
				ostringstream ss;
				ss << pad1Score << " : " << pad2Score;
				score.setString(ss.str());

				window.draw(score);
				window.draw(player1);
				window.draw(esc);
				window.display();


			}
		}

		if (pad1Score != 10 & pad2Score == 10) {

			bool play = true;

			while (play) {

				sf::Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed)
					{
						play = false;
						window.close();
						return 0;
					}
					if ((ev.type == sf::Event::KeyPressed))
					{
						play = false;
						window.close();
						return 0;
					}
				}

				window.clear();
				window.draw(background);
				window.draw(pad1);
				window.draw(pad2);
				window.draw(ball);

				//score
				ostringstream ss;
				ss << pad1Score << " : " << pad2Score;
				score.setString(ss.str());

				window.draw(score);
				window.draw(player2);
				window.draw(esc);
				window.display();


			}
		}





		//rendering
		window.clear();
		window.draw(background);
		window.draw(pad1);
		window.draw(pad2);
		window.draw(ball);

		//score
		ostringstream ss;
		ss << pad1Score << " : " << pad2Score;
		score.setString(ss.str());

		window.draw(score);
		window.display();

	}


	//clean up
	window.close();


	return 0;

}