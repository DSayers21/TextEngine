#pragma once
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <TextEngine/InOutDataManager.h>
#include "SaveLoadControl.h"
#include <TextEngine/InputControl.h>

class StatBlock
{
private:
	double STR, DEX, CON, INT, WIS, CHA;
	int STR_mod, DEX_mod, CON_mod, INT_mod, WIS_mod, CHA_mod;
	double temp_multiplier;
	int proficiency;

	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
	TxtEgn::InputControl m_Input;
public:
	StatBlock();
	StatBlock(double s_val, double d_val, double c_val, double i_val, double w_val, double ch_val);
	~StatBlock();

	//Get Stats
	double GetSTR() { return STR; }
	double GetDEX() { return DEX; }
	double GetCON() { return CON; }
	double GetINT() { return INT; }
	double GetWIS() { return WIS; }
	double GetCHA() { return CHA; }
	int GetProf() { return proficiency; }

	//Set Stats
	void SetSTR(double val) { STR = val; }
	void SetDEX(double val) { DEX = val; };
	void SetCON(double val) { CON = val; }
	void SetINT(double val) { INT = val; }
	void SetWIS(double val) { WIS = val; }
	void SetCHA(double val) { CHA = val; }
	void SetProf(int val) { proficiency = val; }

	//Get Stat Mods
	double GetSTRMod() { return STR_mod; }
	double GetDEXMod() { return DEX_mod; }
	double GetCONMod() { return CON_mod; }
	double GetINTMod() { return INT_mod; }
	double GetWISMod() { return WIS_mod; }
	double GetCHAMod() { return CHA_mod; }

	//Set Stat Mods
	void SetSTRMod(int Mod) { STR_mod = Mod; }
	void SetDEXMod(int Mod) { DEX_mod = Mod; }
	void SetCONMod(int Mod) { CON_mod = Mod; }
	void SetINTMod(int Mod) { INT_mod = Mod; }
	void SetWISMod(int Mod) { WIS_mod = Mod; }
	void SetCHAMod(int Mod) { CHA_mod = Mod; }

	//Get and Set Multiplier
	double GetMultiplier() { return temp_multiplier; }
	void SetMultiplier(double val) { temp_multiplier = val; }

	//Calculate Modifier
	double CalcModifier(double val);

	//Buff De-Buff
	void BuffStat(std::string stat_name, double multiplier);
	void DeBuffStat(std::string stat_name, double multiplier);

	//Save and Load Stat Block
	void StatBlock::Save(std::string FilePath, std::string Name);
	void StatBlock::Load(std::string FilePath);

	std::string BuildPath(std::string FilePath, std::string Name);
};