#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Game;

class LanPowerUp
{
public:
	LanPowerUp(sf::Texture &a, int ID, int type, int x, int y);
	void Render(Game &game);
	int Type();
	int Eaten(sf::Vector2f x, int radius);
	int getID();

private:
	sf::Texture textur;
	sf::Sprite sprite;
	int type2,ID2;
	int distance(sf::Vector2f x, sf::Vector2f y);
};