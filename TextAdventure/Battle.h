#pragma once
#include "Player.h"
#include "Enemies.h"
#include "Dice.h"

#include <TextEngine/COutput.h>
#include <TextEngine/InputControl.h>

enum Commands
{
	Attack, Defend, Run, Help
};
class Battle
{
private:
	TxtEgn::InputControl m_Input;
	//extra D20 is for advantage and disadvantage
	bool PC_first, mob_first;
	bool PC_defending = false;
	bool mob_Defending = false;
	bool defend_prev_turn = false;
	bool action_done = false;
	int roll_for_loot;
	Commands actions;

public:
	Battle();
	Battle(Player* PC, Enemies mob);
	void Encounter(TxtEgn::COutput* Out, Player*, Enemies*);
	~Battle();
};

