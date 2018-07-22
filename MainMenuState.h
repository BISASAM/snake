#pragma once
#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Gamestate.h"

class MainMenuState : public Gamestate
{
public:
	MainMenuState();
	~MainMenuState();
	void HandleEvents(Game& game);
	void Update(Game& game);
	void Draw(Game& game);
	
private:
	void moveup();
	void movedown();
	sf::Font font;
	sf::Text playtxt;
	sf::Text lantxt;
	sf::Text exittxt;
	std::vector<sf::Text> menutxt;
	int Pos;
};

#endif