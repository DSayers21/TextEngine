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

	double GetSTR();
	void SetSTR(double val);
	double GetDEX();
	void SetDEX(double val);
	double GetCON();
	void SetCON(double val);
	double GetINT();
	void SetINT(double val);
	double GetWIS();
	void SetWIS(double val);
	double GetCHA();
	void SetCHA(double val);
	int GetProf();
	void SetProf(int val);

	double GetSTRMod();
	double GetDEXMod();
	double GetCONMod();
	double GetINTMod();
	double GetWISMod();
	double GetCHAMod();

	double CalcModifier(double val);

	void BuffStat(std::string stat_name, double multiplier);
	void DeBuffStat(std::string stat_name, double multiplier);

	double GetMultiplier();
	void SetMultiplier(double val);

	void StatBlock::Save(std::string FilePath, std::string Name);
	void StatBlock::Load(std::string FilePath);

	std::string BuildPath(std::string FilePath, std::string Name);
};