#pragma once
#include "Game.h"

int main()
{
	Game Curve;
	Curve.ChangeState(Game::gameStates::MAINMENU);

	while (Curve.isRunning())
	{
		Curve.Run();
	}

	return 0;
}