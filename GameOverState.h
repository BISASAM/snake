#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Gamestate.h"
#include "eV.h"

class GameOverState : public Gamestate
{
public:
	GameOverState();
	~GameOverState();
	void HandleEvents(Game& game);
	void Update(Game& game);
	void Draw(Game& game);

private:

	std::vector<sf::Color> C;
	sf::Font font;
	sf::Text gameovertxt;
	sf::Text scoretxt;
	sf::Text nextroundtxt;
	sf::Text mainmenutxt;
	std::vector<sf::Text> scoretxts;
	int global;
	int winner;
};
