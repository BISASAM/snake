#pragma once
#include "PowerUp.h"
#include "Game.h"
#include <SFML\OpenGL.hpp>
#include "eV.h"

PowerUp::PowerUp(sf::Texture &a, int type, int lifetime)
{
	lifetime2 = lifetime;
	type2 = type;
	sprite.setTexture(a);
	eT = 0;
	clock.restart().asMicroseconds();
	sprite.setOrigin(24, 24);
}

int PowerUp::Spawn()
{
	rP.x = (rand() % (width-255)) + 30;
	rP.y = (rand() % (height-55)) + 30;
	//std::cout << rP.x << "   "<< rP.y << std::endl;
	std::vector< unsigned char > pixels(30 * 30 * 3);
	glReadBuffer(GL_FRONT); //pixel auslesen
	glReadPixels(rP.x-15, 720-rP.y-15, 20, 20, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
	for (int i = 0; i < pixels.size(); i++)
	{
		//std::cout << std::to_string(pixels[i]) << std::endl;
		if (pixels[i] != 0)
		{
			//std::cout << "Spawn NEIN"<<std::endl;
			return -1;
		}
	}
	sprite.setPosition(sf::Vector2f(rP.x, rP.y));
	//std::cout << "Spawn erfolgreich"<<std::endl;
	return 1;
}


int PowerUp::Type()
{
	return type2;
}

int distance(sf::Vector2f x, sf::Vector2f y)
{
	return sqrt(pow(x.x - y.x, 2) + pow(x.y - y.y, 2));
}

int PowerUp::Eaten(sf::Vector2f x, int radius)
{
	if (distance(sprite.getPosition(),x)<(32+radius))
	{
		return type2;
	}
	else
	{
		return -1;
	}
}

int PowerUp::Time()
{
	eT += clock.restart().asMicroseconds();
	if (eT > lifetime2)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

void PowerUp::Render(Game &game)
{
	game.window.draw(sprite);
}
