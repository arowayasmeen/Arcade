#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "dino.h"

using namespace std;

int dino:: dinof() {

	sf::RenderWindow window(sf::VideoMode(1000, 500), "POKE RUN!");
	window.setFramerateLimit(60);

	sf::Event event;

	//states
	bool play = true;
	bool jump = true;
	bool playerJump = false;
	bool incScore = true;

	//variables
	int azurillPos = 270;
	int cloudPos1 = 0;
	int groundPos = 0;
	int jumpTime;
	int voltorbPos = 1500;
	int lives = 3;
	int pscore = 0;
	int ringPos = 500;

	//images
	sf::Texture azu;
	if (azu.loadFromFile("ResourceDino/azurill.png") == -1) {
		cout << "error";
		return 0;
	}

	sf::Texture volt;
	if (volt.loadFromFile("ResourceDino/voltorb.png") == -1) {
		cout << "error";
		return 0;
	}

	sf::Texture ring;
	if (ring.loadFromFile("ResourceDino/ring.png") == -1) {
		cout << "error";
		return 0;
	}

	sf::Texture sky;
	if (sky.loadFromFile("ResourceDino/sky.png") == -1) {
		cout << "error";
		return 0;
	}
	sf::Texture cloud;
	if (cloud.loadFromFile("ResourceDino/cloud.png") == -1) {
		cout << "error";
		return 0;
	}
	sf::Texture cloud2;
	if (cloud2.loadFromFile("ResourceDino/cloud2.png") == -1) {
		cout << "error";
		return 0;
	}
	sf::Texture cloud3;
	if (cloud3.loadFromFile("ResourceDino/cloud3.png") == -1) {
		cout << "error";
		return 0;
	}
	sf::Texture cloud4;
	if (cloud4.loadFromFile("ResourceDino/cloud4.png") == -1) {
		cout << "error";
		return 0;
	}
	sf::Texture land;
	if (land.loadFromFile("ResourceDino/ground.png") == -1) {
		cout << "error";
		return 0;
	}

	sf::Texture heart;
	if (heart.loadFromFile("ResourceDino/heart.png") == -1) {
		cout << "error";
		return 0;
	}


	//font
	sf::Font font;
	if (font.loadFromFile("ResourceDino/a.ttf") == 0) {
		return 0;
	}


	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(25);
	score.setFillColor(sf::Color::Black);
	score.setPosition(20, 15);

	sf::Text live;
	live.setFont(font);
	live.setCharacterSize(25);
	live.setFillColor(sf::Color::Black);
	live.setPosition(700, 15);
	live.setString("LIVES:");


	sf::Text esc;
	esc.setFont(font);
	esc.setCharacterSize(30);
	esc.setFillColor(sf::Color::Black);
	esc.setPosition(260, 250);
	esc.setString("press any key to exit");

	sf::Text end;
	end.setFont(font);
	end.setCharacterSize(40);
	end.setFillColor(sf::Color::Black);
	end.setPosition(350, 200);
	end.setString("GAME OVER");

	sf::Text resume;
	resume.setFont(font);
	resume.setCharacterSize(30);
	resume.setFillColor(sf::Color::Black);
	resume.setPosition(350, 200);
	resume.setString("You lost a life!");

	sf::Text cont;
	cont.setFont(font);
	cont.setCharacterSize(20);
	cont.setFillColor(sf::Color::Black);
	cont.setPosition(340, 250);
	cont.setString("press any key to continue");

	//sounds
	sf::SoundBuffer jumpbuffer;
	if (jumpbuffer.loadFromFile("ResourceDino/jump1.wav") == 0)return 0;
	sf::Sound azuJump;
	azuJump.setBuffer(jumpbuffer);

	sf::SoundBuffer hitbuffer;
	if (hitbuffer.loadFromFile("ResourceDino/hit.wav") == 0)return 0;
	sf::Sound hit;
	hit.setBuffer(hitbuffer);

	sf::Music pokeMusic;
	if (pokeMusic.openFromFile("ResourceDino/Route1.ogg") == 0)cout << "ok" << endl;
	pokeMusic.setLoop(true);
	pokeMusic.play();

	////shapes
	sf::RectangleShape azurill;
	azurill.setSize(sf::Vector2f(140, 150));
	azurill.setPosition(30, 270);
	azurill.setTexture(&azu);

	sf::CircleShape voltorb;
	voltorb.setRadius(40);
	voltorb.setPosition(1500, 320);
	voltorb.setTexture(&volt);

	sf::CircleShape rings;
	rings.setRadius(40);
	rings.setPosition(300, 150);
	rings.setTexture(&ring);



	sf::RectangleShape skyback;
	skyback.setSize(sf::Vector2f(1000, 400));
	skyback.setPosition(0, 0);
	skyback.setTexture(&sky);

	sf::RectangleShape clouds;
	clouds.setSize(sf::Vector2f(200, 100));
	clouds.setPosition(0, 0);
	clouds.setTexture(&cloud);

	sf::RectangleShape clouds2;
	clouds2.setSize(sf::Vector2f(200, 100));
	clouds2.setPosition(250, 100);
	clouds2.setTexture(&cloud2);

	sf::RectangleShape clouds3;
	clouds3.setSize(sf::Vector2f(200, 100));
	clouds3.setPosition(550, 50);
	clouds3.setTexture(&cloud3);

	sf::RectangleShape clouds4;
	clouds4.setSize(sf::Vector2f(200, 100));
	clouds4.setPosition(850, 110);
	clouds4.setTexture(&cloud4);

	sf::RectangleShape ground;
	ground.setSize(sf::Vector2f(1001, 100));
	ground.setPosition(0, 400);
	ground.setTexture(&land);

	sf::RectangleShape ground2;
	ground2.setSize(sf::Vector2f(1000, 100));
	ground2.setPosition(1000, 400);
	ground2.setTexture(&land);

	sf::RectangleShape heart1;
	heart1.setSize(sf::Vector2f(30, 30));
	heart1.setPosition(820, 15);
	heart1.setTexture(&heart);

	sf::RectangleShape heart2;
	heart2.setSize(sf::Vector2f(30, 30));
	heart2.setPosition(860, 15);
	heart2.setTexture(&heart);

	sf::RectangleShape heart3;
	heart3.setSize(sf::Vector2f(30, 30));
	heart3.setPosition(900, 15);
	heart3.setTexture(&heart);

	while (play) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				playerJump = true;
				jumpTime = 30;
				azurill.setPosition(30, 270);
				azuJump.play();
			}
		}



		//voltorb collision
		if (azurill.getGlobalBounds().intersects(voltorb.getGlobalBounds()) == true) {

			hit.play();
			bool stillplay = true;

			while (stillplay) {

				sf::Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed)
					{
						stillplay = false;

					}
					if ((ev.type == sf::Event::KeyPressed))
					{
						stillplay = false;

					}
				}

				//score
				ostringstream ss;
				ss << "SCORE: " << pscore;
				score.setString(ss.str());

				window.clear();
				window.draw(ground);
				window.draw(ground2);
				window.draw(skyback);
				window.draw(clouds);
				window.draw(clouds2);
				window.draw(clouds3);
				window.draw(clouds4);
				window.draw(azurill);
				window.draw(voltorb);
				window.draw(rings);
				window.draw(resume);
				window.draw(cont);
				window.draw(score);
				window.display();


			}
			lives--;
			voltorbPos = 1000 + (rand() % 200) * 20;
			voltorb.setPosition(voltorbPos, 330);
		}

		//endgame
		if (lives == 0) {
			bool stillplay = true;

			while (stillplay) {

				sf::Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed)
					{
						stillplay = false;
						window.close();
						return 0;
					}
					if ((ev.type == sf::Event::KeyPressed))
					{
						stillplay = false;
						window.close();
						return 0;
					}
				}

				//score
				ostringstream ss;
				ss << "SCORE: " << pscore;
				score.setString(ss.str());

				window.clear();
				window.draw(ground);
				window.draw(ground2);
				window.draw(skyback);
				window.draw(clouds);
				window.draw(clouds2);
				window.draw(clouds3);
				window.draw(clouds4);
				window.draw(azurill);
				window.draw(voltorb);
				window.draw(rings);
				window.draw(esc);
				window.draw(end);
				window.draw(score);
				window.display();


			}

		}

		//ring collision
		if (azurill.getGlobalBounds().intersects(rings.getGlobalBounds())) {

			hit.play();
			pscore = pscore + 100;
			ringPos = 1000 + (rand() % 200) * 20;
		}

		//initial azurill movement

		int x = azurill.getPosition().x;
		int y = azurill.getPosition().y;

		if (playerJump) {
			if (jumpTime) {
				if (jumpTime >= 25)azurill.setPosition(x, y - 25);
				if (jumpTime <= 5)azurill.setPosition(x, y + 25);

			}
			if (jumpTime > 0)jumpTime--;
			else playerJump = false;
		}

		else {
			if (azurillPos == 240)jump = false;
			else if (azurillPos == 270) {
				jump = true;


			}


			if (jump) {
				azurillPos--;
			}
			else azurillPos++;
			azurill.setPosition(30, azurillPos);
		}


		//voltorb movement
		voltorbPos = voltorbPos - 15;
		if (voltorbPos < -80)voltorbPos = 1000 + (rand() % 200) * 20;
		voltorb.setPosition(voltorbPos, 330);

		//ring movement
		ringPos = ringPos - 15;
		if (ringPos < -80)ringPos = 1000 + (rand() % 200) * 20;
		rings.setPosition(ringPos, 150);

		//cloud movement 
		cloudPos1++;
		cloudPos1 = cloudPos1 % 1200;

		if (cloudPos1 == 200) {
			clouds.setPosition(1000, 0);

		}

		if (cloudPos1 == 450) {
			clouds2.setPosition(1000, 100);
		}
		if (cloudPos1 == 750)clouds3.setPosition(1000, 50);
		if (cloudPos1 == 1050)clouds4.setPosition(1000, 110);

		clouds.move(-1, 0);
		clouds2.move(-1, 0);
		clouds3.move(-1, 0);
		clouds4.move(-1, 0);

		//ground movement
		groundPos++;
		if (groundPos == 1000)ground.setPosition(1000, 400);
		if (groundPos == 2000) {
			ground.setPosition(0, 400);
			ground2.setPosition(1000, 400);
		}
		ground.move(-1, 0);
		ground2.move(-1, 0);
		groundPos = groundPos % 2000;

		//Score
		if (voltorbPos > 1000)incScore = true;
		if (voltorbPos < 0 && incScore) {
			pscore++;
			incScore = false;
		}



		//render

		//score
		ostringstream ss;
		ss << "SCORE: " << pscore;
		score.setString(ss.str());

		window.clear();
		window.draw(ground);
		window.draw(ground2);
		window.draw(skyback);
		window.draw(clouds);
		window.draw(clouds2);
		window.draw(clouds3);
		window.draw(clouds4);
		window.draw(azurill);
		window.draw(voltorb);
		window.draw(rings);
		window.draw(score);
		window.draw(live);
		window.draw(heart1);
		if (lives > 1)window.draw(heart2);
		if (lives > 2)window.draw(heart3);
		window.display();


	}

	window.close();
	return 0;




}