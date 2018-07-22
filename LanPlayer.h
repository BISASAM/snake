#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\OpenGL.hpp>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <cmath> 
#include "PowerUp.h"
#include "Timer.h"

class Game;

class LanPlayer
{
public:
	LanPlayer();
	void create(sf::Color col, sf::Vector2<int> pos, sf::Keyboard::Key K1, sf::Keyboard::Key K2);
	void Update(float &elapsedTime);
	void Draw(Game& game);
	void PchangeSpeed(float s);
	void PchangeThickness(int d);
	void changeKeys();
	sf::Vector2f getHead();
	sf::Vector2<float> R;
	sf::VertexArray vertices;
	std::pair<int, double> allPPowerUp;
	bool gameoverB = false;
	bool startphase;
	bool drawBorder;
	bool hole = false;


private:

	std::vector< unsigned char > pixels;
	std::vector< unsigned char > pixelsSide1;
	std::vector< unsigned char > pixelsSide2;

	float norm(sf::Vector2f r);

	void Collision();
	void Timerdesolve();
	std::vector<std::pair<Timer, int>> TimersandType;
	sf::Font font;
	sf::Text playtxt;
	sf::CircleShape circle;
	sf::Keyboard::Key Key1, Key2,KeyTemp;
	sf::RectangleShape rect;
	static sf::Texture arrowtxt;
	sf::Sprite arrow;
	sf::Color Col, oldCol;
	sf::Vector2f Pos, N, LP, RP, holeStart;
	int n = 0;
	int m = 0;
	int eT, holetimer, holedis, traceN, radius,dis;
	int randomN;
	bool Peaten = false;
	float speed, turnspeed, alpha;
};