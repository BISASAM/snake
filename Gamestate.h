#pragma once
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

class Game; //vorwaertsdeklaration

class Gamestate
{
public:
	virtual void HandleEvents(Game& game) = 0;
	virtual void Update(Game& game) = 0;
	virtual void Draw(Game& game) = 0;
	virtual		 ~Gamestate() {};
};

#endif