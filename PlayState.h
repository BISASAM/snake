#pragma once
#include <iostream>
#include<SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\OpenGL.hpp>
//#include "Gamestate.h"
#include "Game.h"
#include "Gamestate.h"
#include "eV.h"
//#include <vector>
#include "PowerUp.h"
#include "Player.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include <cmath> 


class PlayState : public Gamestate
{
public:
	PlayState();
	~PlayState();
	void HandleEvents(Game& game);
	void Update(Game& game);
	void Draw(Game& game);
	std::vector<Player> players;
	bool drawBorder = true;
	
private:

	void HandlePowerups();
	void allPapplyPU();
	sf::Clock clock;
	std::vector<sf::Color> C;
	std::vector<sf::Keyboard::Key> K;
	sf::Font font;
	sf::Text scoretxt;
	std::vector<sf::Text> scoretxts;
	sf::RectangleShape rectsplit;
	sf::RectangleShape border;
	sf::Texture turtlegreen, turtlered, blitzgreen, blitzred, duengreen, dickred, controlswitch, radierer, dBorder;
	std::vector<Timer> vTimer;
	
	float elapsedTime;
	int pTime, pTime2,gameovercounter, gameovercounterold,randomP, w;
};