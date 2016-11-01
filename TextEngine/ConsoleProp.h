#pragma once

//Includes
#include <iostream>
#include <windows.h>

namespace TxtEgn
{
	class ConsoleProp
	{
	public:
		//Basic Constructor
		ConsoleProp();
		//Destructor
		~ConsoleProp();
		//Copy Constructor
		ConsoleProp(const ConsoleProp& other);
		//Equal operator
		ConsoleProp operator=(const ConsoleProp &other);
		//Init function to initialise the ConsoleProp
		void Init(int FontX, int FontY, int StartX, int StartY, unsigned short Colour, bool togFullscreen);
		//Returns the current x position of the cursor in the console
		int wherex();
		//Returns the current y position of the cursor in the console
		int wherey();
		//Reverts the colour to the colour previously in use by the console
		void RevertColour();
		//Sets the new cursor position to the x and y passed in
		void gotoxy(int x, int y);
		//Ends the current line of the console setting the cursor to the start position on the next line
		void EndLine();
		//Updates the console to where things currently are
		void Update();

		//Getters
		//Returns the current font size
		int GetFontSize(HANDLE windowHandle, COORD *size);
		//Returns the StartX value
		int GetStartX() { return _StartX; }
		//Returns the StartY value
		int GetStartY() { return _StartY; }
		//Returns the Current Y value
		int GetCurrentY() { return _CurrentY; }
		//Returns the width of the font
		int GetFontX() { return _FontX; }
		//Returns the height of the font
		int GetFontY() { return _FontY; }
		//Returns the active colour in the consoleProp
		int GetColour() { return _Colour; }
		//Returns the last colour used in the consoleProp
		int GetPrevColour() { return _PrevColour; }
		//Returns the current width of the consoleProp
		int GetConsoleWidth() { return _Width; }
		//Returns the width of the CONSOLE
		int FindConsoleWidth();

		//Setters
		//Sets the font size
		void SetFont(int FontX, int FontY);
		//Sets the active colour
		void SetColour(unsigned short Colour);
		//Sets the previous colour
		void SetPrevColour(unsigned short Colour) { _PrevColour = Colour; }
		//Sets the current y value of the consoleProp
		void SetCurrentY(int CurrentY) { _CurrentY = CurrentY; }
		//Sets the start x value for the consoleProp
		void SetStartX(int StartX) { _StartX = StartX; }
		//Sets the width of the consoleProp
		void SetConsoleWidth(int Width) { _Width = Width; }
		//Toggles the fullscreen state of the CONSOLE
		void ToggleFull();
	private:
		//Updates the Font to the font held in the ConsoleProp
		int UpdateFont();
		//Sets the colour to the _Colour member variable
		void UpdateColour();
		
	protected:
		//Member variables for ConsoleProp, these are protected as are inherited by ConsoleZone
		int _FontX, _FontY, _StartX, _StartY, _CurrentY, _Width;
		unsigned short _Colour;
		unsigned short _PrevColour;
	};
}