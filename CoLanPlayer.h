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

class CoLanPlayer
{
public:
	CoLanPlayer();
	CoLanPlayer(sf::Color col, sf::Vector2<int> pos);
	void Update(sf::Vector2f(r));
	void Draw(Game& game);
	void PchangeThickness(int d);
	sf::Vector2f getHead();
	sf::Vector2<float> R;
	sf::VertexArray vertices;
	bool gameoverB = false;
	bool startphase;
	bool hole = false;


private:

	float norm(sf::Vector2f r);
	sf::Clock clock;
	void Timerdesolve();
	std::vector<std::pair<Timer, int>> TimersandType;
	sf::Font font;
	sf::Text playtxt;
	sf::CircleShape circle;
	static sf::Texture arrowtxt;
	sf::Sprite arrow;
	sf::Color Col, Col2;
	sf::Vector2f oldPos, Pos, N, LP, RP, holeStart;
	int n = 0;
	int m = 0;
	int eT, holetimer, holedis, traceN, radius,dis;
	int randomN;
	bool Peaten = false;
	float alpha;
};