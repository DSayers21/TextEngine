#include "ConsoleZone.h"



ConsoleZone::ConsoleZone()
{
}


ConsoleZone::~ConsoleZone()
{
}

void ConsoleZone::Init(int Width, int StartX, int StartY, int CurrentY, int FontX, int FontY, unsigned short Colour)
{
	SetFont(FontX, FontY);
	SetColour(Colour);
	SetPrevColour(Colour);

	_Width = Width;
	_StartX = StartX;
	_StartY = StartY;
	_CurrentY = CurrentY;

	gotoxy(_StartX, _CurrentY);
}