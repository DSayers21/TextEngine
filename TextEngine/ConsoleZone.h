#pragma once
#include "ConsoleProp.h"
class ConsoleZone :
	public ConsoleProp
{
public:
	ConsoleZone();
	~ConsoleZone();

	void Init(int Width, int StartX, int StartY, int CurrentY, int FontX, int FontY, unsigned short Colour);
};

