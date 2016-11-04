#include "Battle.h"


Battle::Battle()
{

}

Battle::Battle(Player* PC, Enemies mob)
{
}

Battle::~Battle()
{
}

bool Battle::Encounter(TxtEgn::COutput* Out, Player* PC, Enemies* mob)
{
	Dice D20(20);
	int Temp1, Temp2;
	std::vector<std::string> HelpList{ "Attack", "Defend", "Run", "Help" };
	std::string input;

	Out->GetConsole()->SetColour(7);

	Out->WriteSlow("A " + mob->getName() + " comes outta nowhere!!", true);



	while (PC->GetHP() != 0 || mob->getHP() != 0)
	{
		if (PC->GetHP() <= 0)
		{
			break;
		}
		else
		{
			//if (PC->PC_Stats.GetDEX() > mob->stats.GetDEX())
			Out->WriteSlow("You have " + std::to_string(PC->GetHP()) + "HP left.", true);
			Out->WriteSlow("It is your turn, choose an action. (Type Help to list commands):", true);
			
			input = m_Input.ParseIntoSentence(Out->GetInput("What do you do? >"), 0);

			if (m_Input.CompareStrings(input, "Attack"))
				actions = Attack;
			if (m_Input.CompareStrings(input, "Defend"))
				actions = Defend;
			if (m_Input.CompareStrings(input, "Run"))
				actions = Run;
			if (m_Input.CompareStrings(input, "Help"))
				actions = Help;

			switch (actions)
			{
				case Attack:
				{
					switch (mob_Defending)
					{
						case true:
						{
							Temp1 = D20.Roll() + PC->GetStatBlock().GetSTRMod();					//first roll
							Temp2 = D20.Roll() + PC->GetStatBlock().GetSTRMod();			//second roll
							int Smallest;
							if (Temp2 < Temp1)
							{
								Smallest = Temp2;
							}
							else
							{
								if (Temp1 >= mob->getAC())
								{
									Out->WriteSlow("You hit the " + mob->getName(), true);
									mob->TakeDamage(PC->WeaponAttack(PC->GetWeapon(), mob));
								}
								else
									Out->WriteSlow("You miss the " + mob->getName(), true);
							}
							break;
						}
						case false:
						{
							Temp1 = D20.Roll() + PC->GetStatBlock().GetSTRMod();
							if (Temp1 >= mob->getAC())
							{
								Out->WriteSlow("You hit the " + mob->getName(), true);
								mob->TakeDamage(PC->WeaponAttack(PC->GetWeapon(), mob));
							}
							else
								Out->WriteSlow("You miss the " + mob->getName(), true);
							break;
						}
					}
					break;
				}
				case Defend:
				{
					Out->WriteSlow("you try and defend yourself...", true);
					PC_defending = true;
					break;
				}
				case Run:
				{
					Temp1 = D20.Roll() + PC->GetStatBlock().GetDEXMod();
					Temp2 = D20.Roll() + mob->stats.GetDEXMod();

					if (Temp1 >= Temp2 + mob->stats.GetDEXMod())
					{
						Out->WriteSlow("You're too slow! The " + mob->getName() + " senses an opening and strikes!", true);
						Temp2 = D20.Roll() + mob->stats.GetSTRMod();
						if (Temp2 >= PC->GetAC())
						{
							PC->SetHP(PC->GetHP() - mob->Attack());
						}
					}
					break;
				}
				case Help:
				{
					Out->DisplayTextBox(HelpList, '*', 14);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		//enemy turn starts here
		if (mob->getHP() <= 0)
			break;
		else
		{
			Out->WriteSlow(mob->getName() + " has " + std::to_string(mob->getHP()) + "HP left.", true);
			Out->WriteSlow("it's the " + mob->getName() + "'s turn!", true);
			if (mob->getHP() < (20 * (mob->getMaxHP() / 100)))		//if health is below 20%
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
					Temp1 = D20.Roll() + mob->stats.GetSTRMod();					//first roll
					Temp2 = D20.Roll() + mob->stats.GetSTRMod();			//second roll

					if (Temp2 < Temp1)
					{
						Temp1 = Temp2;
					}
					else if (Temp1 >= mob->getAC())
					{
						Out->WriteSlow("The " + mob->getName() + " hits you!", true);
						PC->SetHP(PC->GetHP() - mob->Attack());
					}
					else
						Out->WriteSlow("The " + mob->getName() + " misses you!", true);
					break;
				case false:
					Temp1 = D20.Roll() + mob->stats.GetSTRMod();
					if (Temp1 >= PC->GetAC())
					{
						Out->WriteSlow("The " + mob->getName() + " hits you!", true);
						PC->SetHP(PC->GetHP() - mob->Attack());
					}
					else
						Out->WriteSlow("The " + mob->getName() + " misses you!", true);
					break;
				}
			}
		}
	}
	if (mob->getHP() <= 0)
	{
		roll_for_loot = D20.Roll();

		Out->WriteSlow("You defeated " + mob->getName() + "! You gain " + std::to_string(mob->getEXP()) + " XP and " + std::to_string(mob->getGold()) + " Gold!", true);

		if (roll_for_loot % 2 == 0)
			Out->WriteSlow("You loot the " + mob->getName() + " and find " + mob->getLootName() + "!", true);

		PC->AddEXP(mob->getEXP());
		PC->SetPlyrGold(PC->GetPlyrGold() + mob->getGold());
		PC->AddItem(mob->getLoot());

		return true;
	}
	else
	{
		Out->WriteSlow("You have fallen!", true);
		return false;
		//player dies
	}
}
