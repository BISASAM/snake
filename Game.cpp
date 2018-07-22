#pragma once
#include "Game.h"
#include "eV.h"

int width;
int height;

Game::Game()
{
	window.create(sf::VideoMode(1280, 720,32), "Client");
	window.setMouseCursorVisible(false);
	running = true;
	width = window.getSize().x;
	height = window.getSize().y;
}

void Game::Run()
{
	while (window.isOpen())
	{
		window.clear();
		
		CurrentState->HandleEvents(*this);
		CurrentState->Update(*this);
		CurrentState->Draw(*this);

		window.display();
	}
}

bool Game::isRunning()
{
	return running;
}

void Game::ChangeState(gameStates newState)
{
	switch (newState)
	{
	case gameStates::MAINMENU:
		CurrentState = std::move(std::unique_ptr<MainMenuState>(new MainMenuState));
		break;

	case gameStates::PLAYERSELECT:
		CurrentState = std::move(std::unique_ptr<PlayerSelectState>(new PlayerSelectState));
		break;

	case gameStates::PLAY:
		CurrentState = std::move(std::unique_ptr<PlayState>(new PlayState));
		break;
	case gameStates::GAMEOVER:
		CurrentState = std::move(std::unique_ptr<GameOverState>(new GameOverState));
		break;
	case gameStates::LOBBY:
		CurrentState = std::move(std::unique_ptr<LobbyState>(new LobbyState));
		break;
	case gameStates::LANPLAY:
		CurrentState = std::move(std::unique_ptr<LanPlayState>(new LanPlayState));
		break;
	}
}