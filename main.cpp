#include <SFML/Graphics.hpp>
#include <iostream>
#include "pong.h"
#include "dino.h"
#include "snakeMain.h"
#include "tron.h"
#include "ttt.h"


using namespace std;

using namespace sf;

//constants
int windowWidth =800,windowHeight = 500;
float ballRadius = 10.f, ballVelocity = 5.f;
float paddleWidth = 100.f, paddleHeight = 20.f, paddleVelocity = 10.f;
float blockWidth = 60.f, blockHeight = 20.f;
int countBlocksX = 10, countBlocksY = 5;
bool play = true;
sf::Texture texBall;

//creating the ball

class Ball {
public:
	//shape of the ball

	CircleShape shape;

	//movement of the ball
	Vector2f velocity
	{
		-ballVelocity, -ballVelocity
	};

	//constuctor of the ball
	Ball(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::White);
		shape.setOrigin(ballRadius, ballRadius);
		shape.setTexture(&texBall);
		
	}
	//position of the ball
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getRadius(); }
	float right() { return x() + shape.getRadius(); }
	float top() { return y() - shape.getRadius(); }
	float bottom() { return y() + shape.getRadius(); }
	//to move
	void update()
	{
		shape.move(velocity);
		//keeping the ball inside the screen
		if (left() < 0) velocity.x = ballVelocity;
		else if (right() > windowWidth) velocity.x = -ballVelocity;
		if (top() < 0) velocity.y = ballVelocity;
		else if (bottom() > windowHeight)
		{
			play = false;
		}

	}
};

class Paddle {
public:
	//Shape of Paddle
	RectangleShape shape;
	Vector2f velocity;

	//Constructor
	Paddle(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setSize({ paddleWidth, paddleHeight });
		shape.setFillColor(Color::Red);
		shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
	}

	//position of the paddle
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.f; }
	float right() { return x() + shape.getSize().x / 2.f; }
	float top() { return y() - shape.getSize().y / 2.f; }
	float bottom() { return y() + shape.getSize().y / 2.f; }
	void update()
	{
		shape.move(velocity);

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) velocity.x = -paddleVelocity;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth) velocity.x = paddleVelocity;
		else velocity.x = 0;

	}

};

class Brick {
public:
	RectangleShape shape;
	bool destroyed = false;

	//constructor
	Brick(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setSize({ blockWidth, blockHeight });
		shape.setFillColor(Color::Yellow);
		shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
	}
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.f; }
	float right() { return x() + shape.getSize().x / 2.f; }
	float top() { return y() - shape.getSize().y / 2.f; }
	float bottom() { return y() + shape.getSize().y / 2.f; }

};

//checking if two shapes are colliding
template<class T1, class T2> bool isIntersecting(T1 &mA, T2 &mB)
{
	return mA.right() >= mB.left() && mA.left() <= mB.right() && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

//for paddle and ball collision
void testCollision(Paddle &mPaddle, Ball &mBall) {

	if (!isIntersecting(mPaddle, mBall))//no collision
		return;
	mBall.velocity.y = -ballVelocity;//pushing the ball upwards
									 //directing it where the paddle was hit
	if (mBall.x() < mPaddle.x())
		mBall.velocity.x = -ballVelocity;
	else mBall.velocity.x = ballVelocity;
}
//for ball and brick collision
void testBrickCollision(Brick &mBrick, Ball &mBall)
{
	if (!isIntersecting(mBrick, mBall)) return;

	mBrick.destroyed = true;//marking

							//check from which side it collides
	float overlapLeft{ mBall.right() - mBrick.left() };
	float overlapRight{ mBrick.right() - mBall.left() };
	float overlapTop{ mBall.bottom() - mBrick.top() };
	float overlapBottom{ mBrick.bottom() - mBall.top() };

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < overlapBottom);
	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
		mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
	else
		mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}

int dxballf()
{

	//Variables
	play = true;
	Ball ball(windowWidth / 2, windowHeight / 2);
	Paddle paddle((float)windowWidth / 2.f, (float)windowHeight-5 );

	vector<Brick> bricks;//contains bricks

	for (int i = 0; i < countBlocksX; i++)//col
	{
		for (int j = 0; j < countBlocksY; j++)//row
		{
			bricks.emplace_back((i + 1)*(blockWidth + 3) + 22, (j + 2)*(blockHeight + 3));//emplace constructs bricks
		}
	}

	//this is the game window
	RenderWindow window(VideoMode(windowWidth, windowHeight), "DXBall");

	window.setFramerateLimit(60);//normal time is 60fps




								 //Game loop
	while (play)
	{
		//Describing the window
		window.clear(Color::Black);

		//esc closes the game loop
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			play = false;


		ball.update();
		paddle.update();

		testCollision(paddle, ball);

		for (int a = 0; a < bricks.size(); a++)
		{
			testBrickCollision(bricks[a], ball);
		}

		//use a built in function to remove the destroyed bricks
		bricks.erase(remove_if(begin(bricks), end(bricks), [](const Brick& mBrick) {return mBrick.destroyed; }), end(bricks));

		//showing window content
		window.draw(ball.shape);
		window.draw(paddle.shape);
		for (int i = 0; i < bricks.size(); i++) window.draw(bricks[i].shape);
		window.display();
	}
	return 0;
}




int main() {

	sf::RenderWindow window(sf::VideoMode(1100, 600), "TT'S ARCADE!");
	window.setFramerateLimit(60);

	//images
	sf::Font font1;
	if (font1.loadFromFile("a.ttf") == 0) {
		return 0;
	}

	sf::Text t;
	t.setFont(font1);
	t.setCharacterSize(50);
	t.setFillColor(sf::Color::White);
	t.setPosition(100, 50);
	t.setString("TT'S ARCADE");

	sf::Texture texBackground;
	if (texBackground.loadFromFile("mainback.png") == 0)return 0;
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(1100, 600));
	background.setPosition(0, 0);
	background.setTexture(&texBackground);

	sf::Texture texPong;
	if (texPong.loadFromFile("pong.png") == 0)return 0;
	sf::Texture texDino;
	if (texDino.loadFromFile("dino.png") == 0)return 0;
	sf::Texture texSnek;
	if (texSnek.loadFromFile("snek.png") == 0)return 0;
	sf::Texture texTron;
	if (texTron.loadFromFile("tron.png") == 0)return 0;
	sf::Texture texTic;
	if (texTic.loadFromFile("ttt.png") == 0)return 0;
	sf::Texture texDx;
	if (texDx.loadFromFile("dxball.png") == 0)return 0;
	
	if (texBall.loadFromFile("ball2.png") == 0)return 0;
	

	//states
	bool play = true;

	//variables


	//shapes
	sf::RectangleShape rect1;
	rect1.setSize(sf::Vector2f(150,150));
	rect1.setPosition(100, 200);
	rect1.setFillColor(sf::Color::White);
	rect1.setTexture(&texPong);

	sf::RectangleShape rect2;
	rect2.setSize(sf::Vector2f(150, 150));
	rect2.setPosition(300, 200);
	rect2.setFillColor(sf::Color::White);
	rect2.setTexture(&texDino);

	sf::RectangleShape rect3;
	rect3.setSize(sf::Vector2f(150, 150));
	rect3.setPosition(500, 200);
	rect3.setFillColor(sf::Color::White);
	rect3.setTexture(&texSnek);

	sf::RectangleShape rect4;
	rect4.setSize(sf::Vector2f(150, 150));
	rect4.setPosition(100, 400);
	rect4.setFillColor(sf::Color::White);
	rect4.setTexture(&texTron);

	sf::RectangleShape rect5;
	rect5.setSize(sf::Vector2f(150, 150));
	rect5.setPosition(300, 400);
	rect5.setFillColor(sf::Color::White);
	rect5.setTexture(&texTic);

	sf::RectangleShape rect6;
	rect6.setSize(sf::Vector2f(150, 150));
	rect6.setPosition(500, 400);
	rect6.setFillColor(sf::Color::White);
	rect6.setTexture(&texDx);

	while (play) {

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
				pong p;
				p.pongf();
				
			
			}

			
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
				dino d;
				d.dinof();


			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
				snakeMain s;
				s.snakef();


			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4) {
				tron t;
				t.tronf();


			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5) {
				ttt tt;
				tt.tttf();


			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) {
				dxballf();


			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (sf::Mouse::getPosition(window).x >= rect1.getPosition().x && sf::Mouse::getPosition(window).x <= rect1.getPosition().x + 150 && sf::Mouse::getPosition(window).y >= rect1.getPosition().y && sf::Mouse::getPosition(window).y <= rect1.getPosition().y + 150) {
					pong p;
					p.pongf();
				}

				if (sf::Mouse::getPosition(window).x >= rect2.getPosition().x && sf::Mouse::getPosition(window).x <= rect2.getPosition().x + 150 && sf::Mouse::getPosition(window).y >= rect2.getPosition().y && sf::Mouse::getPosition(window).y <= rect2.getPosition().y + 150) {
					dino d;
					d.dinof();
				}

				if (sf::Mouse::getPosition(window).x >= rect3.getPosition().x && sf::Mouse::getPosition(window).x <= rect3.getPosition().x + 150 && sf::Mouse::getPosition(window).y >= rect3.getPosition().y && sf::Mouse::getPosition(window).y <= rect3.getPosition().y + 150) {
					snakeMain s;
					s.snakef();
				}

				if (sf::Mouse::getPosition(window).x >= rect4.getPosition().x && sf::Mouse::getPosition(window).x <= rect4.getPosition().x + 150 && sf::Mouse::getPosition(window).y >= rect4.getPosition().y && sf::Mouse::getPosition(window).y <= rect4.getPosition().y + 150) {
					tron t;
					t.tronf();
				}

				if (sf::Mouse::getPosition(window).x >= rect5.getPosition().x && sf::Mouse::getPosition(window).x <= rect5.getPosition().x + 150 && sf::Mouse::getPosition(window).y >= rect5.getPosition().y && sf::Mouse::getPosition(window).y <= rect5.getPosition().y + 150) {
					ttt tt;
					tt.tttf();
				}

				if (sf::Mouse::getPosition(window).x >= rect6.getPosition().x && sf::Mouse::getPosition(window).x <= rect6.getPosition().x + 150 && sf::Mouse::getPosition(window).y >= rect6.getPosition().y && sf::Mouse::getPosition(window).y <= rect6.getPosition().y + 150) {
					dxballf();
				}


			}
		}

		//render
		window.clear();
		window.draw(background);
		window.draw(t);
		window.draw(rect1);
		window.draw(rect2);
		window.draw(rect3);
		window.draw(rect4);
		window.draw(rect5);
		window.draw(rect6);
		window.display();
	}


	window.close();
}