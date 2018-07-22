#pragma once
#pragma once
#include <SFML\Graphics.hpp>

class Timer
{
public:
	Timer(int time);
	~Timer();
	bool TimerCheck();
	void restart();

private:
	int time2;
	sf::Clock clock;
	int z;
};