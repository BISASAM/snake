#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Game;

class PowerUp
{
public:
	PowerUp(sf::Texture &a, int type, int lifetime);
	void Render(Game &game);
	int Type();
	int Eaten(sf::Vector2f x, int radius);
	int Time();
	int Spawn();
	
private:
	sf::Clock clock;
	sf::Texture textur;
	sf::Sprite sprite;
	sf::Vector2<int> rP;

	int type2, lifetime2,eT;
	bool Active;
};