#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "MainMenuState.h"
#include "PlayerSelectState.h"
#include "PlayState.h"
#include "GameOverState.h"
#include "LobbyState.h"
#include "LanPlayState.h"

class Game
{
public:
	Game();
	enum class gameStates { MAINMENU, PLAYERSELECT, PLAY, GAMEOVER, LOBBY, LANPLAY };
	void Run();
	bool isRunning();
	void ChangeState(gameStates newstate);
	bool running;
	sf::RenderWindow window;
	std::unique_ptr<Gamestate> CurrentState;

private:
	
};

#endif