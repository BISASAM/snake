#pragma once
#include "Timer.h"


Timer::Timer(int time)
{
	time2 = time;
	z = 0;
	clock.restart();
}

bool Timer::TimerCheck()
{
	if (z > time2)
	{
		return true;
	}
	else
	{
		z += clock.restart().asMicroseconds();
		return false;
	}
}

void Timer::restart()
{
	z = 0;
}

Timer::~Timer()
{
}