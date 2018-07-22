#pragma once
#include "PlayState.h"
#include "eV.h"
#include "Game.h"

std::vector<int> score;
std::vector<int> scoreOld;
std::vector<PowerUp> powerups;

PlayState::PlayState()
{
	pTime = 0;
	pTime2 = 0;
	gameovercounterold = 0;
	score.resize(Number,0);
	scoreOld.resize(Number, 0);
	//setup
	//PowerUp testuren
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
	scoretxt.setPosition(width -150, 50);
	scoretxt.setCharacterSize(30);
	scoretxt.setString("Score:");
	scoretxt.setFillColor(sf::Color(220, 220, 220));

	border.setFillColor(sf::Color::Transparent);
	border.setSize(sf::Vector2f(width - 200, height));
	border.setOutlineThickness(-5);
	border.setOutlineColor(sf::Color(250, 150, 100));

	Timer T(3000000);
	vTimer.push_back(T);
	randomP = 5000000;
	w = 0;

	C.resize(4);
	C[0] = sf::Color::Blue;
	C[1] = sf::Color::Red;
	C[2] = sf::Color::Green;
	C[3] = sf::Color::Yellow;
	K.resize(8);
	K[0] = sf::Keyboard::Right;
	K[1] = sf::Keyboard::S;
	K[2] = sf::Keyboard::B;
	K[3] = sf::Keyboard::Numpad3;
	K[4] = sf::Keyboard::Left;
	K[5] = sf::Keyboard::A;
	K[6] = sf::Keyboard::V;
	K[7] = sf::Keyboard::Numpad2;

	for (int i = 0; i < score.size(); i++)
	{
		scoreOld[i] = score[i];
	}

	for (int i = 0; i < Number; i++)
	{
		sf::Vector2<int> x((rand() % (width-280))+20, (rand() % (height-40))+20);
		Player nP(C[i], x, K[i], K[i + 4]);
		nP.startphase = true;
		players.push_back(nP);
	}

	for (int i = 0; i<Number; i++)
	{
		sf::Text a;
		a.setFont(font);
		a.setPosition(width - 150, 100 + i * 50);
		a.setCharacterSize(30);
		a.setFillColor(C[i]);
		scoretxts.push_back(a);
	}
}

void PlayState::HandleEvents(Game& game)
{
	elapsedTime = clock.restart().asMicroseconds();
	pTime += elapsedTime;
	pTime2 += elapsedTime;
	

	std::vector<bool> PlayerGOStatus(Number);
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
				score.clear();
				scoretxts.clear();
				Number = 0;
				game.ChangeState(Game::gameStates::MAINMENU);
			}
			break;
		}

	}

	if (Number == 1 && players[0].gameoverB == true)
	{
		w += elapsedTime;
		if (w > 1500000)
		{	
			w = 0;
			game.ChangeState(Game::gameStates::GAMEOVER);
		}
	}

	if (Number > 1)
	{
		gameovercounter = 0;
		for (int i = 0; i < players.size(); i++)
		{
			if (players[i].gameoverB == true)
			{
				gameovercounter++;
			}
		}

		if (gameovercounter > gameovercounterold)
		{
			for (int i = 0; i < players.size(); i++)
			{
				if (players[i].gameoverB == false)
				{
					score[i]++;
				}
			}
		}

		if (gameovercounter >= Number - 1)
		{
			w += elapsedTime;
			if (w > 1500000)
			{
				w = 0;
				game.ChangeState(Game::gameStates::GAMEOVER);
			}
		}
		gameovercounterold = gameovercounter;
		gameovercounter = 0;
	}

}

void PlayState::allPapplyPU()
{
	for (int i = 0; i < players.size(); i++)
	{
		switch (players[i].allPPowerUp.first)
		{
		case -1:
			break;
		case 1:
			for (int j = 0; j < players.size(); j++)
			{
				players[j].PchangeSpeed(players[i].allPPowerUp.second);
			}
			players[i].allPPowerUp.first = -1;
			players[i].allPPowerUp.second = 1;
			break;
		case 3:
			for (int j = 0; j < players.size(); j++)
			{
				players[j].PchangeSpeed(players[i].allPPowerUp.second);
			}
			players[i].allPPowerUp.first = -1;
			players[i].allPPowerUp.second = 1;
			break;
		case 5:
			for (int j = 0; j < players.size(); j++)
			{
				players[j].PchangeThickness(players[i].allPPowerUp.second);
			}
			players[i].allPPowerUp.first = -1;
			players[i].allPPowerUp.second = 1;
			break;
		case 6:
			for (int j = 0; j < players.size(); j++)
			{
				players[j].changeKeys();
			}
			players[i].allPPowerUp.first = -1;
			players[i].allPPowerUp.second = 1;
			break;
		case 7:
			for (int j = 0; j < players.size(); j++)
			{
				//players[j].vertices.erase(players[j].vertices.begin(), players[j].vertices.end() - 2);
				players[j].vertices.clear();
			}
			players[i].allPPowerUp.first = -1;
			players[i].allPPowerUp.second = 1;
			break;
		case 8:
			if (drawBorder == true)
			{
				drawBorder = false;
				for (int j = 0; j < players.size(); j++)
				{
					players[j].drawBorder = false;
				}
			}
			else
			{
				drawBorder = true;
				for (int j = 0; j < players.size(); j++)
				{
					players[j].drawBorder = true;
				}
			}
			players[i].allPPowerUp.first = -1;
			players[i].allPPowerUp.second = 1;
			break;
		}
	}
}

void PlayState::HandlePowerups()
{
	//powerups spawnen
	if (pTime2 > randomP)
	{
		pTime2 = 0;
		randomP = (rand() % 6) * 500000 + 4000000;
		//std::cout << randomP <<std::endl;
		int z = rand() % 9;
		if (z == 0)
		{
			PowerUp Pow(turtlegreen, 0,10000000);
			int p=Pow.Spawn();
			if (p == 1) {
				powerups.push_back(Pow);
			}
		}
		else if (z == 1)
		{
			PowerUp Pow(turtlered, 1,10000000);
			int p = Pow.Spawn();
			if (p == 1) {
				powerups.push_back(Pow);
			}
		}
		else if (z == 2)
		{
			PowerUp Pow(blitzgreen, 2, 10000000);
			int p = Pow.Spawn();
			if (p == 1) {
				powerups.push_back(Pow);
			}
		}
		else if (z == 3)
		{
			PowerUp Pow(blitzred, 3, 10000000);
			int p = Pow.Spawn();
			if (p == 1) {
				powerups.push_back(Pow);
			}
		}
		else if (z == 4)
		{
			PowerUp Pow(duengreen, 4, 10000000);
			int p = Pow.Spawn();
			if (p == 1) {
				powerups.push_back(Pow);
			}
		}
		else if (z == 5)
		{
			PowerUp Pow(dickred, 5, 10000000);
			int p = Pow.Spawn();
			if (p == 1) {
				powerups.push_back(Pow);
			}
		}
		else if (z == 6)
		{
			PowerUp Pow(controlswitch, 6, 10000000);
			int p = Pow.Spawn();
			if (p == 1) {
				powerups.push_back(Pow);
			}
		}
		else if (z == 7)
		{
			PowerUp Pow(radierer, 7, 10000000);
			int p = Pow.Spawn();
			if (p == 1) {
				powerups.push_back(Pow);
			}
		}
		else if (z == 8)
		{
			PowerUp Pow(dBorder, 8, 10000000);
			int p = Pow.Spawn();
			if (p == 1) {
				powerups.push_back(Pow);
			}
		}
	}

	//check PowerUp Time
	for (int i = 0; i < powerups.size(); i++)
	{
		int m = powerups[i].Time();
		if(m==1)
		powerups.erase(powerups.begin() + i);
	}
}

void PlayState::Update(Game& game)
{	
	HandlePowerups();

	int i = vTimer.size();
	if (i > 0) {
		if (vTimer[i - 1].TimerCheck() == true)
		{
			for (int j = 0; j < players.size(); j++)
			{
				players[j].startphase = false;
			}
			vTimer.clear();
		}
	}

	for (int i = 0; i < players.size(); i++)
	{
		players[i].Update(elapsedTime);
	}
	allPapplyPU();
}

void PlayState::Draw(Game& game)
{
	for (int i = 0; i < players.size(); i++)
	{
		players[i].Draw(game);
	}

	for (int i = 0; i < powerups.size(); i++) {
		powerups[i].Render(game);
	}

	game.window.draw(rectsplit);
	game.window.draw(scoretxt);

	for (int i = 0; i < scoretxts.size(); i++)
	{
		scoretxts[i].setString(std::to_string(score[i]));
		game.window.draw(scoretxts[i]);
	}

	if (drawBorder == true)
	{
		game.window.draw(border);
	}
	
	
}

PlayState::~PlayState()
{
	std::cout << "GameScreen destruktor wurde aufgerufen" << std::endl;
}