#pragma once
//Includes
#include "ConsoleProp.h"

namespace TxtEgn
{
	//Inherits from ConsoleProp
	class ConsoleZone :
		public ConsoleProp
	{
	public:
		//Constructor
		ConsoleZone();
		//Destructor
		~ConsoleZone();
		//Init function
		void Init(int Width, int StartX, int StartY, int CurrentY, int FontX, int FontY, unsigned short Colour);
	};
}