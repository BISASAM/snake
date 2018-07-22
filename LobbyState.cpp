#pragma once
#include "LobbyState.h"
#include "eV.h"

std::vector<std::vector<int>> connectionInfo;

LobbyState::LobbyState()
{
	font.loadFromFile("Jokerman.TTF");

	cStatus.setFont(font); 
	cStatus.setCharacterSize(20);
	cStatus.setString("disconnected..");
	cStatus.setFillColor(sf::Color(220, 220, 220));
	cStatus.setOrigin(cStatus.getLocalBounds().width/2, cStatus.getLocalBounds().height / 2);
	cStatus.setPosition(width / 2, height / 2-300);

	playertxt.setFont(font);
	playertxt.setCharacterSize(20);
	playertxt.setString("Du bist Player ?");
	playertxt.setFillColor(sf::Color(220, 220, 220));
	playertxt.setOrigin(playertxt.getLocalBounds().width / 2, playertxt.getLocalBounds().height / 2);
	playertxt.setPosition(width / 2, height / 2 - 250);

	lobbytxt.setFont(font); 
	lobbytxt.setCharacterSize(20);
	lobbytxt.setString("In Lobby:");
	lobbytxt.setFillColor(sf::Color(220, 220, 220));
	lobbytxt.setOrigin(0, lobbytxt.getLocalBounds().height / 2);
	lobbytxt.setPosition(width -1000, height / 2 - 150);

	ptemp.setFont(font);
	ptemp.setCharacterSize(20);
	ptemp.setString("ä");
	ptemp.setFillColor(sf::Color(220, 220, 220));
	ptemp.setOrigin(0, ptemp.getLocalBounds().height / 2);
	ptemp.setPosition(width - 850, height / 2 - 100);

	starttxt.setFont(font);
	starttxt.setCharacterSize(20);
	starttxt.setString("Press Enter to Start the Game...");
	starttxt.setFillColor(sf::Color(220, 220, 220));
	starttxt.setOrigin(starttxt.getLocalBounds().width / 2, starttxt.getLocalBounds().height / 2);
	starttxt.setPosition(width /2, height - 100);

	C.resize(4);
	C[0] = sf::Color::Blue;
	C[1] = sf::Color::Red;
	C[2] = sf::Color::Green;
	C[3] = sf::Color::Yellow;
	
	t1 = sf::milliseconds(10);
	NSetup();

}

void LobbyState::HandleEvents(Game& game)
{
	sf::Event event;
	while (game.window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			game.window.close();
			game.running = false;
			break;

		case sf::Event::KeyPressed:

			if (event.key.code == sf::Keyboard::Escape)
			{
				game.ChangeState(Game::gameStates::MAINMENU);
			}

			if (event.key.code == sf::Keyboard::Return)
			{
				if (P1 == true)
				{
					gamestart << int(2);
					socket.send(gamestart);
					game.ChangeState(Game::gameStates::LANPLAY);
					return;
				}
				
			}
			break;
		}
	}
}

void LobbyState::Update(Game& game)
{
	if (selector.wait(t1)) //check for data
	{
		if (selector.isReady(socket))//test socket for recv data
		{
			sf::Packet packet;

			if (socket.receive(packet) != sf::Socket::Done)
			{
				std::cout << "recieve FAIL" << std::endl;
			}
			else
			{
				InBox(packet, game);		
			}
		}
	}
}

void LobbyState::Draw(Game& game)
{
	game.window.draw(cStatus);
	game.window.draw(playertxt);
	game.window.draw(lobbytxt);
	for (int i = 0; i < playerIDs.size(); i++)
	{
		game.window.draw(playerIDs[i]);
	}

	if (playerIDs.size() > 0)
	{
		if (P1 == true)
		{
			game.window.draw(starttxt);
		}
	}
}

void LobbyState::NSetup()
{
	sf::Socket::Status status = socket.connect("127.0.0.1", 54345);
	if (status != sf::Socket::Done)
	{
		std::cout << "socket connect error" << std::endl;
	}
	else
	{
		selector.add(socket);
		cStatus.setString("connected to 127.0.0.1");
		cStatus.setOrigin(cStatus.getLocalBounds().width / 2, cStatus.getLocalBounds().height / 2);
	}
}

void LobbyState::InBox(sf::Packet packet, Game& game)
{
	int x = 0;
	packet >> x;

	if (x == 1)
	{
		UpdateLobby(packet);
	}

	if (x == 2)
	{
		Gamestart(game);
	}
	
}

void LobbyState::UpdateLobby(sf::Packet info)
{
	int self = 0; //ID-indikator
	int playerID = 0;
	info >> self >> playerID;

	if (playerID == 0)
	{
		playerIDs.clear();
		connectionInfo.clear();
		P1 = false;
	}
	ptemp.setString(std::string("Player ") + std::to_string(playerID + 1));
	ptemp.setFillColor(C[playerID]);
	ptemp.setPosition(width - 850, height / 2 - 100 + playerID * 50);
	playerIDs.push_back(ptemp);

	std::vector<int> vtemp;
	vtemp.push_back(self);
	vtemp.push_back(playerID);
	connectionInfo.push_back(vtemp);

	if (self == 1)
	{
		if (playerID == 0) { P1 = true; }
		playertxt.setString(std::string("Du bist Player ") + std::to_string(playerID + 1) + std::string(" !"));
		playertxt.setFillColor(C[playerID]);
	}
}

void LobbyState::Gamestart(Game& game)
{
	game.ChangeState(Game::gameStates::LANPLAY);
	return;
}

LobbyState::~LobbyState()
{
	std::cout << "Lobbydestruktor wurde aufgerufen" << std::endl;
}