#pragma once
#include "GameOverState.h"
#include "eV.h"

GameOverState::GameOverState()
{
	font.loadFromFile("Jokerman.TTF");

	gameovertxt.setFont(font);
	
	scoretxt.setFont(font);
	scoretxt.setPosition(width - 150, 50);
	scoretxt.setCharacterSize(30);
	scoretxt.setString("Score:");
	scoretxt.setFillColor(sf::Color(220, 220, 220));

	nextroundtxt.setFont(font);
	nextroundtxt.setPosition(50, height - 120);
	nextroundtxt.setCharacterSize(20);
	nextroundtxt.setString("Press Enter for Next Round");
	nextroundtxt.setFillColor(sf::Color(220, 220, 220));

	mainmenutxt.setFont(font);
	mainmenutxt.setPosition(50, height - 80);
	mainmenutxt.setCharacterSize(20);
	mainmenutxt.setString("Press Escape for Main Menu");
	mainmenutxt.setFillColor(sf::Color(220, 220, 220));

	winner = 0;

	C.resize(4);
	C[0] = sf::Color::Blue;
	C[1] = sf::Color::Red;
	C[2] = sf::Color::Green;
	C[3] = sf::Color::Yellow;

	for (int i = 0; i < Number; i++)
	{
		sf::Text a;
		a.setFont(font);
		a.setPosition(width - 150, 100 + i * 50);
		a.setCharacterSize(30);
		a.setFillColor(C[i]);
		scoretxts.push_back(a);
	}

	powerups.clear();

	for (int i = 0; i < score.size(); i++)
	{
		if(score[i]-scoreOld[i]==Number-1)
		{
			winner = i;
		}
	}
	gameovertxt.setString("Player    " + std::to_string(winner+1)+"    gewinnt!");
	gameovertxt.setFillColor(C[winner]);
	
	if (Number==1)
	{
		gameovertxt.setString("Gameover");
		gameovertxt.setFillColor(sf::Color::Red);
	}

	gameovertxt.setCharacterSize(40);
	gameovertxt.setOrigin(gameovertxt.getLocalBounds().width / 2, gameovertxt.getLocalBounds().height / 2);
	gameovertxt.setPosition(width / 2, height / 2);
	
}

void GameOverState::HandleEvents(Game &game)
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
			if (event.key.code == sf::Keyboard::Return)
			{
				game.ChangeState(Game::gameStates::PLAY);
				break;
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				score.clear();
				scoretxts.clear();
				Number = 0;
				game.ChangeState(Game::gameStates::MAINMENU);
				break;
			}
		}
	}
}

void GameOverState::Update(Game& game)
{

}

void GameOverState::Draw(Game& game)
{
	game.window.draw(gameovertxt);
	game.window.draw(scoretxt);
	game.window.draw(nextroundtxt);
	game.window.draw(mainmenutxt);

	for (int i = 0; i < scoretxts.size(); i++)
	{
		scoretxts[i].setString(std::to_string(score[i]));
		game.window.draw(scoretxts[i]);
	}
	
}

GameOverState::~GameOverState()
{
	std::cout << "GameOverState wurde zerstoerst" << std::endl;
}