#pragma once

#include <iostream>
#include <windows.h>

class ConsoleProp
{
public:
	ConsoleProp();
	~ConsoleProp();

	ConsoleProp(const ConsoleProp& other);

	ConsoleProp operator=(const ConsoleProp &other);

	void Init(int FontX, int FontY, int StartX, int StartY, unsigned short Colour, bool togFullscreen);

	int wherex();
	int wherey();
	void RevertColour();
	void gotoxy(int x, int y);
	void EndLine();
	void Update();

	//Getters
	int GetFontSize(HANDLE windowHandle, COORD *size);
	int GetStartX();
	int GetStartY();
	int GetCurrentY();
	int GetFontX();
	int GetFontY();
	int GetColour();
	int GetPrevColour();
	int GetConsoleWidth();
	int FindConsoleWidth();

	//Setters
	void SetFont(int FontX, int FontY);
	void SetColour(unsigned short Colour);
	void SetPrevColour(unsigned short Colour);
	void SetCurrentY(int CurrentY);
	void SetStartX(int StartX);
	void SetConsoleWidth(int Width);
private:
	int UpdateFont();
	void UpdateColour();
	void ToggleFull();
protected:
	int _FontX, _FontY, _StartX, _StartY, _CurrentY, _Width;
	unsigned short _Colour;
	unsigned short _PrevColour;
};