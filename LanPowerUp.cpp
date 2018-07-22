#pragma once
#include "LanPowerUp.h"
#include "Game.h"
#include <SFML\OpenGL.hpp>
#include "eV.h"

LanPowerUp::LanPowerUp(sf::Texture &a, int ID, int type, int x, int y)
{
	ID2 = ID;
	type2 = type;
	sprite.setTexture(a);
	sprite.setOrigin(24, 24);
	sprite.setPosition(x, y);
}

int LanPowerUp::Type()
{
	return type2;
}

int LanPowerUp::distance(sf::Vector2f x, sf::Vector2f y)
{
	return sqrt(pow(x.x - y.x, 2) + pow(x.y - y.y, 2));
}

int LanPowerUp::getID()
{
	return ID2;
}

int LanPowerUp::Eaten(sf::Vector2f x, int radius)
{
	if (distance(sprite.getPosition(), x)<(32 + radius))
	{
		return type2;
	}
	else
	{
		return -1;
	}
}

void LanPowerUp::Render(Game &game)
{
	game.window.draw(sprite);
}
