#pragma once
#ifndef EV_H
#define EV_H
#include "PowerUp.h"
#include "LanPowerUp.h"
extern int Number, width, height;
extern std::vector<int> score;
extern std::vector<int> scoreOld;
extern std::vector<PowerUp> powerups;
extern std::vector<LanPowerUp> Lpowerups;
extern std::vector<std::vector<int>> connectionInfo;
#endif