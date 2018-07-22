#pragma once
#include "PlayerSelectState.h"

int Number;

PlayerSelectState::PlayerSelectState()
{
	width = 1280;
	height = 720;

	font.loadFromFile("Jokerman.TTF");
	
	atxt.setFont(font);
	atxt.setOrigin(40, 40);
	atxt.setPosition(width / 2 - 100, height / 2);
	atxt.setCharacterSize(30);
	atxt.setString("# Player");
	atxt.setFillColor(sf::Color(220, 220, 220));
	
	btxt.setFont(font);
	btxt.setOrigin(40, 40);
	btxt.setPosition(width / 2 + 100, height / 2);
	btxt.setCharacterSize(30);
	btxt.setString("1");
	btxt.setFillColor(sf::Color::Red);
	
	c.setFont(font);
	c.setCharacterSize(20);
	c.setString("Controls:");
	c.setFillColor(sf::Color(220, 220, 220));

	d.setFont(font);
	d.setCharacterSize(20);
	d.setString("P1: LEFT / RIGHT -Arrows");
	d.setFillColor(sf::Color::Blue);

	e.setFont(font);
	e.setCharacterSize(20);
	e.setString("P2: A / S -Keys");
	e.setFillColor(sf::Color::Red);

	f.setFont(font);
	f.setCharacterSize(20);
	f.setString("P3: V / B -Keys");
	f.setFillColor(sf::Color::Green);

	g.setFont(font);
	g.setCharacterSize(20);
	g.setString("P4: Numpad 2 / 3 -Keys");
	g.setFillColor(sf::Color::Yellow);

	Controls.push_back(c);
	Controls.push_back(d);
	Controls.push_back(e);
	Controls.push_back(f);
	Controls.push_back(g);

	instructtxt.setFont(font);
	instructtxt.setCharacterSize(20);
	instructtxt.setString("Use UP-/Down- Arrow Keys");
	instructtxt.setFillColor(sf::Color(220, 220, 220));
	instructtxt.setOrigin(instructtxt.getLocalBounds().width / 2, instructtxt.getLocalBounds().height / 2-50);
	instructtxt.setPosition(width/2, height/2);

	Number = 1;
}

void PlayerSelectState::moveup()
{
	Number++;
	if (Number > 4)
		Number = 1;
	btxt.setString(std::to_string(Number));
}

void PlayerSelectState::movedown()
{
	Number--;
	if (Number <1)
		Number = 4;
	btxt.setString(std::to_string(Number));
}

void PlayerSelectState::HandleEvents(Game &game)
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
					game.ChangeState(Game::gameStates::PLAY);
					break;
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					game.ChangeState(Game::gameStates::MAINMENU);
					break;
				}
			}
	}
}

void PlayerSelectState::Update(Game& game)
{
	for (int i=0; i < Number+1; i++) 
	{
		Controls[i].setPosition(50, height - 50 -(Number+1) * 30 + i * 30);
	}
}

void PlayerSelectState::Draw(Game& game)
{
	game.window.draw(atxt);
	game.window.draw(btxt);
	game.window.draw(instructtxt);
	
	for (int i=0; i < Number+1; i++)
	{
		game.window.draw(Controls[i]);
	}
	
}

PlayerSelectState::~PlayerSelectState()
{
	std::cout << "PlaySelectState wurde zerstoerst" << std::endl;
}