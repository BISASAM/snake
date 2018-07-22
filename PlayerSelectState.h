#pragma once
#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Gamestate.h"
#include "eV.h"

class PlayerSelectState : public Gamestate
{
public:
	PlayerSelectState();
	~PlayerSelectState();
	void HandleEvents(Game& game);
	void Update(Game& game);
	void Draw(Game& game);

private:
	
	void moveup();
	void movedown();
	sf::Font font;
	sf::Text atxt, btxt,c,d,e,f,g, instructtxt;
	std::vector<sf::Text> Controls;
	int width, height;
};

#endif