#pragma once
#include "LanPlayState.h"
#include "eV.h"

std::vector<LanPowerUp> Lpowerups;

LanPlayState::LanPlayState()
{
	turtlegreen.loadFromFile("0.png"); //sich selber langsam
	turtlered.loadFromFile("1.png");//andere langsam
	blitzgreen.loadFromFile("2.png");//sich selber schnell
	blitzred.loadFromFile("3.png");//andere schnell
	duengreen.loadFromFile("4.png"); //sich selber duenn
	dickred.loadFromFile("5.png");//andere dick
	controlswitch.loadFromFile("6.png");//andere Controls verdrehen
	radierer.loadFromFile("7.png");//Spuren löschen
	dBorder.loadFromFile("8.png");//Rand öffnen

	rectsplit.setSize(sf::Vector2f(5, height));
	rectsplit.setPosition(sf::Vector2f(width - 200, 0));
	rectsplit.setFillColor(sf::Color(180, 180, 180));

	font.loadFromFile("Jokerman.TTF");
	scoretxt.setFont(font);
	scoretxt.setPosition(width - 150, 50);
	scoretxt.setCharacterSize(30);
	scoretxt.setString("Score:");
	scoretxt.setFillColor(sf::Color(220, 220, 220));

	border.setFillColor(sf::Color::Transparent);
	border.setSize(sf::Vector2f(width - 200, height));
	border.setOutlineThickness(-5);
	border.setOutlineColor(sf::Color(250, 150, 100));

	C.resize(4);
	C[0] = sf::Color::Blue;
	C[1] = sf::Color::Red;
	C[2] = sf::Color::Green;
	C[3] = sf::Color::Yellow;

	CoLanPlayers.resize(connectionInfo.size());
	CoLPcreated.resize(connectionInfo.size(), false);

	t1 = sf::milliseconds(10);
	NSetup();
	Gamestart();

	
}

void LanPlayState::NSetup()
{
	sf::Socket::Status status = socket.connect("127.0.0.1", 54345);
	if (status != sf::Socket::Done)
	{
		std::cout << "socket connect error" << std::endl;
	}
	else
	{
		selector.add(socket);
	}
}

void LanPlayState::Gamestart()
{
	//herausfinden welcher Spielen man ist + erstellen

	for (int i = 0; i < connectionInfo.size(); i++)
	{
		if (connectionInfo[i][0] == 1)
		{
			selfID = connectionInfo[i][1];
		}
	}

	//sf::Vector2<int> x((rand() % (width - 280)) + 20, (rand() % (height - 40)) + 20);
	sf::Vector2<int> x(400, 400);
	PlayerOne.create(C[selfID], x, sf::Keyboard::S, sf::Keyboard::A);
	PlayerOne.startphase = false; //false macht probleme wenn collision an
	sf::Packet packet;
	packet << int(3) << selfID << int(PlayerOne.getHead().x) << int(PlayerOne.getHead().y);
	for (int i = 0; i < 10; i++) {//10x senden da 1x unzuverlässig
		socket.send(packet);
	}

}

void LanPlayState::HandleEvents(Game& game)
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

			}
			
			if (event.key.code == sf::Keyboard::Return)
			{
				
			}
			break;
		}
	}
}

void LanPlayState::Update(Game& game)
{
	eT = clock.restart().asMicroseconds();
	PlayerOne.Update(eT);

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
				InBox(packet);
			}
		}
	}

	sf::Packet packet; //seine eigene Position versenden
	packet << int(4) << selfID << int(PlayerOne.getHead().x) << int(PlayerOne.getHead().y);
	socket.send(packet);

	//löcher senden
	if (POneHoleOld==false && PlayerOne.hole == true)
	{
		POneHoleOld = true;
		sf::Packet packet; //
		packet << int(5) << selfID << int(1);
		socket.send(packet);
	}
	else if (POneHoleOld == true && PlayerOne.hole == false)
	{
		POneHoleOld = false;
		sf::Packet packet; 
		packet << int(5) << selfID << int(0);
		socket.send(packet);
	}
}

void LanPlayState::Draw(Game& game)
{
	game.window.draw(rectsplit);
	game.window.draw(scoretxt);

	if (drawBorder == true)
	{
		game.window.draw(border);
	}
	
	PlayerOne.Draw(game);

	for(int i=0; i < CoLanPlayers.size(); i++)
	{
		CoLanPlayers[i].Draw(game);
	}

	for (int i = 0; i < Lpowerups.size(); i++) {
		Lpowerups[i].Render(game);
	}

}

void LanPlayState::InBox(sf::Packet packet)
{
	int a;
	packet >> a;
	if (a == 3) //infos zum erstellen der coplayer
	{
		createCoPlayer(packet);
	}
	else if (a == 4) //infos zum bewegen der coplayer
	{
		moveCoPlayer(packet);
	}
	else if (a == 5) //infos zu löchern
	{
		holeCoPlayer(packet);
	}
	else if (a == 6) //spawn powerup
	{
		spawnPowerups(packet);
	}
	else if (a == 7) //erase Powerup
	{
		erasePowerups(packet);
	}
}

void LanPlayState::createCoPlayer(sf::Packet packet)
{
	int a, b, c;
	packet >> a >> b >> c;
	std::cout <<"Colanplayer erstellt mit ID: "<< a << "         " << b << "         " << c << "         " << std::endl;
	if(CoLPcreated[a] == false) 
	{
		CoLanPlayer tP(C[a], sf::Vector2<int>(b, c));// Position vom coplayer
		CoLanPlayers[a] = tP;
		CoLPcreated[a] = true;
	}
	//std::cout << CoLanPlayers.size() << std::endl;
}

void LanPlayState::moveCoPlayer(sf::Packet packet)
{
	int a, b, c;
	packet >> a >> b >> c;
	//std::cout << a << "         " << b << "         " << c << "         " << c << std::endl;
	CoLanPlayers[a].Update(sf::Vector2f(b, c));
}

void LanPlayState::holeCoPlayer(sf::Packet packet)
{
	int a, b;
	packet >> a >> b;
	//std::cout << a << "         " << b << std::endl;
	if (b == 1) {
		CoLanPlayers[a].hole = true;
	}
	if (b == 0) {
		CoLanPlayers[a].hole = false;
	}
}

void LanPlayState::spawnPowerups(sf::Packet packet)
{
	int b; //ID
	int c; //type
	int x; //x-koordinate
	int y; //y-koordinate

	packet >> b >> c >> x >> y;
	std::cout << b <<"      " << c << std::endl;
		if (c == 0)
		{
			LanPowerUp Pow(turtlegreen, b, c, x, y);
			Lpowerups.push_back(Pow);
		}
		else if (c == 1)
		{
			LanPowerUp Pow(turtlered, b, c, x, y);
			Lpowerups.push_back(Pow);
			
		}
		else if (c == 2)
		{
			LanPowerUp Pow(blitzgreen, b, c, x, y);
			Lpowerups.push_back(Pow);
			
		}
		else if (c == 3)
		{
			LanPowerUp Pow(blitzred, b, c, x, y);
			Lpowerups.push_back(Pow);
			
		}
		else if (c == 4)
		{
			LanPowerUp Pow(duengreen, b, c, x, y);
			Lpowerups.push_back(Pow);
			
		}
		else if (c == 5)
		{
			LanPowerUp Pow(dickred, b, c, x, y);
			Lpowerups.push_back(Pow);
			
		}
		else if (c == 6)
		{
			LanPowerUp Pow(controlswitch, b, c, x, y);
			Lpowerups.push_back(Pow);
			
		}
		else if (c == 7)
		{
			LanPowerUp Pow(radierer, b, c, x, y);
			Lpowerups.push_back(Pow);
			
		}
		else if (c == 8)
		{
			LanPowerUp Pow(dBorder, b, c, x, y);
			Lpowerups.push_back(Pow);
			
		}
}

void LanPlayState::erasePowerups(sf::Packet packet)
{
	int b; //ID
	packet >> b;
	for (int i = 0; i < Lpowerups.size(); i++)
	{
		if (Lpowerups[i].getID() == b)
		{
			Lpowerups.erase(Lpowerups.begin() + i);
		}
	}
	std::cout << "erase powerup mit ID   " <<  b << std::endl;
}

LanPlayState::~LanPlayState()
{
	std::cout << "LanPlayState wurde zerstört" << std::endl;
}