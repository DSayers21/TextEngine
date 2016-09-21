#pragma once

#include <iostream>
#include <windows.h>

namespace TxtEgn
{
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
		int GetStartX() { return _StartX; }
		int GetStartY() { return _StartY; }
		int GetCurrentY() { return _CurrentY; }
		int GetFontX() { return _FontX; }
		int GetFontY() { return _FontY; }
		int GetColour() { return _Colour; }
		int GetPrevColour() { return _PrevColour; }
		int GetConsoleWidth() { return _Width; }
		int FindConsoleWidth();

		//Setters
		void SetFont(int FontX, int FontY);
		void SetColour(unsigned short Colour);
		void SetPrevColour(unsigned short Colour) { _PrevColour = Colour; }
		void SetCurrentY(int CurrentY) { _CurrentY = CurrentY; }
		void SetStartX(int StartX) { _StartX = StartX; }
		void SetConsoleWidth(int Width) { _Width = Width; }

		void ToggleFull();
	private:
		int UpdateFont();
		void UpdateColour();
		
	protected:
		int _FontX, _FontY, _StartX, _StartY, _CurrentY, _Width;
		unsigned short _Colour;
		unsigned short _PrevColour;
	};
}