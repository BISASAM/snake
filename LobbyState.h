#pragma once
#ifndef LOBBYSTATE_HPP
#define LOBBYSTATE_HPP

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Gamestate.h"
#include <SFML\Network.hpp>

class LobbyState : public Gamestate
{
public:
	LobbyState();
	~LobbyState();
	void HandleEvents(Game& game);
	void Update(Game& game);
	void Draw(Game& game);
	

private:
	void Gamestart(Game& game);
	void NSetup();
	void InBox(sf::Packet packet, Game& game);
	void UpdateLobby(sf::Packet info);


	sf::TcpSocket socket;
	sf::SocketSelector selector;
	sf::Time t1;
	sf::Packet gamestart;

	sf::Font font;
	sf::Text cStatus;
	sf::Text lobbytxt;
	sf::Text playertxt;
	sf::Text ptemp;
	sf::Text starttxt;
	std::vector<sf::Color> C;
	

	std::vector<sf::Text> playerIDs;

	bool P1 = false;
};

#endif