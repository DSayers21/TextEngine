#include "Battle.h"



Battle::Battle(Player* PC, Enemies mob)
{
}

Battle::~Battle()
{
}



void Battle::Encounter(Player* PC, Enemies mob)
{
	std::string input;
	std::cout << "\n A " << mob.getName() << " comes outta nowhere!!\n";
	while (PC->GetHP() != 0 || mob.getHP() != 0)
	{
		if (PC->GetHP() <= 0)
		{
			break;
		}
		else
		{
			//if (PC->PC_Stats.GetDEX() > mob.stats.GetDEX())
			std::cout << "\nYou have " << PC->GetHP() << "HP left.";
			std::cout << "\nIt is your turn, choose an action. (Type Help to list commands):\n";
			std::cout << ">";
			std::cin >> input;
			if (input == "Attack")
				actions = Attack;
			else if (input == "Defend")
				actions = Defend;
			else if (input == "Run")
				actions = Run;
			else if (input == "Help")
				actions = Help;

			switch (actions)
			{
			case Attack:
				switch (mob_Defending)
				{
				case true:
					D20 = RollD20() + PC->PC_Stats.GetSTRMod();					//first roll
					extra_D20 = RollD20() + PC->PC_Stats.GetSTRMod();			//second roll

					if (extra_D20 < D20)
					{
						D20 = extra_D20;
					}
					else
					{
						if (D20 >= mob.getAC())
						{
							std::cout << "\nYou hit the " << mob.getName();
							mob.TakeDamage(PC->WeaponAttack(PC->getWeapon(), mob));
						}
						else
							std::cout << "\nYou miss the " << mob.getName();
					}

					break;
				case false:
					D20 = Battle::RollD20() + PC->PC_Stats.GetSTRMod();
					if (D20 >= mob.getAC())
					{
						std::cout << "\nYou hit the " << mob.getName();
						mob.TakeDamage(PC->WeaponAttack(PC->getWeapon(), mob));
					}
					else
						std::cout << "\nYou miss the " << mob.getName();
					break;
				}
				break;
			case Defend:
				std::cout << "\nyou try and defend yourself...";
				PC_defending = true;
				break;
			case Run:
				D20 = RollD20() + PC->PC_Stats.GetDEXMod();
				mob_D20 = RollD20() + mob.stats.GetDEXMod();
				if (D20 >= mob_D20 + mob.stats.GetDEXMod())
				{
					std::cout << "\nYou're too slow! The " << mob.getName() << " senses an opening and strikes!";
					mob_D20 = RollD20() + mob.stats.GetSTRMod();
					if (mob_D20 >= PC->getAC())
					{
						PC->SetHP(PC->GetHP() - mob.Attack());
					}
				}
				break;
			case Help:
				std::cout << "\nAttack\nDefend\nRun\nHelp\n";
				break;
			default:
				break;
			}
		}
		//enemy turn starts here
		if (mob.getHP() <= 0)
			break;
		else
		{
			std::cout << "\n" << mob.getName() << " has " << mob.getHP() << "HP left.";
			std::cout << "\n\nit's the " << mob.getName() << "'s turn!";
			if (mob.getHP() < (20 * (mob.getMaxHP() / 100)))		//if health is below 20%
			{
				switch (defend_prev_turn)
				{
				case true:
					mob_Defending = false;
					defend_prev_turn = false;
					break;
				case false:
					mob_Defending = true;
					defend_prev_turn = true;
					break;
				}

			}
			else
			{
				switch (PC_defending)
				{
				case true:
					D20 = RollD20() + mob.stats.GetSTRMod();					//first roll
					extra_D20 = RollD20() + mob.stats.GetSTRMod();				//second roll

					if (extra_D20 < D20)
					{
						D20 = extra_D20;
					}
					else if (D20 >= mob.getAC())
					{
						std::cout << "\nThe " << mob.getName() << " hits you!";
						PC->SetHP(PC->GetHP() - mob.Attack());
					}
					else
						std::cout << "\nThe " << mob.getName() << " misses you!";
					break;
				case false:
					D20 = RollD20() + mob.stats.GetSTRMod();
					if (D20 >= PC->getAC())
					{
						std::cout << "\nThe " << mob.getName() << " hits you!";
						PC->SetHP(PC->GetHP() - mob.Attack());
					}
					else
						std::cout << "\nThe " << mob.getName() << " misses you!";
					break;
				}
			}
		}

	}
	if (mob.getHP() <= 0)
	{
		roll_for_loot = RollD20();

		std::cout << "\nYou defeated " << mob.getName() << "! You gain " << mob.getEXP() << " XP and " << mob.getGold() << " Gold!\n";

		if (roll_for_loot % 2 == 0)
			std::cout << "You loot the " << mob.getName() << " and find " << mob.getLootName() << "!\n";

		PC->AddEXP(mob.getEXP());
		PC->SetMoney(PC->GetMoney() + mob.getGold());
		PC->AddItem(mob.getLoot());
	}
	else
	{
		std::cout << "\n\nYou have fallen!\n";
		//player dies
	}
}
