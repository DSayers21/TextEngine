#pragma once
#include "Player.h"
#include "Enemies.h"
#include <stdlib.h>
#include <time.h>

enum Commands
{
	Attack, Defend, Run, Help
};
class Battle
{
private:

	int D20 = RollD20();
	int mob_D20 = RollD20();
	int extra_D20 = RollD20();						//extra D20 is for advantage and disadvantage
	bool PC_first, mob_first;
	bool PC_defending = false;
	bool mob_Defending = false;
	bool defend_prev_turn = false;
	bool action_done = false;
	int roll_for_loot;
	Commands actions;

public:
	Battle(Player* PC, Enemies mob);
	int RollD20();
	void Encounter( Player*, Enemies);
	~Battle();
};

