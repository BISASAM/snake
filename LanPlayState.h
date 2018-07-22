#pragma once
#ifndef LANPLAYSTATE_HPP
#define LANPLAYSTATE_HPP

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Gamestate.h"
#include <SFML\Network.hpp>
#include "Player.h"
#include "LanPlayer.h"
#include "CoLanPlayer.h"

class LanPlayState : public Gamestate
{
public:
	LanPlayState();
	~LanPlayState();
	void HandleEvents(Game& game);
	void Update(Game& game);
	void Draw(Game& game);
	
private:
	void NSetup();
	void InBox(sf::Packet packet);
	void Gamestart();
	void createCoPlayer(sf::Packet packet);
	void moveCoPlayer(sf::Packet packet);
	void holeCoPlayer(sf::Packet packet);
	void spawnPowerups(sf::Packet packet);
	void erasePowerups(sf::Packet packet);

	sf::Texture turtlegreen, turtlered, blitzgreen, blitzred, duengreen, dickred, controlswitch, radierer, dBorder;
	sf::RectangleShape rectsplit, border;
	sf::Font font;
	sf::Text scoretxt;
	std::vector<sf::Color> C;
	bool drawBorder = true;

	sf::Clock clock;
	float eT;

	int selfID = 0;

	LanPlayer PlayerOne;
	std::vector<CoLanPlayer> CoLanPlayers;
	std::vector<bool> CoLPcreated;

	sf::TcpSocket socket;
	sf::SocketSelector selector;
	sf::Time t1;

	bool POneHoleOld = false;
};

#endif