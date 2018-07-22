#pragma once
#include "MainMenuState.h"
#include "eV.h"

MainMenuState::MainMenuState()
{
font.loadFromFile("Jokerman.TTF");

playtxt.setFont(font); //Pos=0
playtxt.setOrigin(40, 40);
playtxt.setPosition(width / 2, height / 2);
playtxt.setCharacterSize(30);
playtxt.setString("Play!");
playtxt.setFillColor(sf::Color::Red);

lantxt.setFont(font); //Pos=1
lantxt.setOrigin(40, 40);
lantxt.setPosition(width / 2, height / 2 + 50);
lantxt.setCharacterSize(30);
lantxt.setString("Lan!");
lantxt.setFillColor(sf::Color(220, 200, 220));

exittxt.setFont(font); ////Pos=2
exittxt.setOrigin(40, 40);
exittxt.setPosition(width / 2, height / 2 + 100);
exittxt.setCharacterSize(30);
exittxt.setString("Exit!");
exittxt.setFillColor(sf::Color(220, 200, 220));

menutxt.push_back(playtxt);
menutxt.push_back(lantxt);
menutxt.push_back(exittxt);


Pos = 0;

}

void MainMenuState::moveup()
{
	menutxt[Pos].setFillColor(sf::Color(220, 200, 220));
	Pos--;
	if (Pos < 0)
		Pos = 2;
	menutxt[Pos].setFillColor(sf::Color::Red);
}

void MainMenuState::movedown()
{
	menutxt[Pos].setFillColor(sf::Color(220, 200, 220));
	Pos++;
	if (Pos > 2)
		Pos = 0;
	menutxt[Pos].setFillColor(sf::Color::Red);
}

void MainMenuState::HandleEvents(Game& game)
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
			if (event.key.code == sf::Keyboard::Up)
			{
				moveup();
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				movedown();
			}
			if (event.key.code == sf::Keyboard::Return)
			{
				switch (Pos)
				{
				case 0:
					game.ChangeState(Game::gameStates::PLAYERSELECT);
					break;
				case 1:
					game.ChangeState(Game::gameStates::LOBBY);
					break;
				case 2:
					game.window.close();
					game.running = false;
					break;
				}
			}
			break;
		}
	}
}

void MainMenuState::Update(Game& game)
{

}

void MainMenuState::Draw(Game& game)
{
	for (int i = 0; i < menutxt.size(); i++)
	{
		game.window.draw(menutxt[i]);
	}
}

MainMenuState::~MainMenuState()
{
	std::cout << "Menuedestruktor wurde aufgerufen" << std::endl;
}