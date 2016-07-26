#include "ConsoleProp.h"

namespace TxtEgn
{
	ConsoleProp::ConsoleProp() : _StartX(0), _CurrentY(0), _Width(0)
	{
	}

	ConsoleProp::~ConsoleProp()
	{
	}

	ConsoleProp::ConsoleProp(const ConsoleProp& other)
	{
		_FontX = other._FontX;
		_FontY = other._FontY;
		_Colour = other._Colour;
		_PrevColour = other._PrevColour;
		_StartX = other._StartX;
		_CurrentY = other._CurrentY;
		_Width = other._Width;
	}

	ConsoleProp ConsoleProp::operator=(const ConsoleProp &other)
	{
		_FontX = other._FontX;
		_FontY = other._FontY;
		_Colour = other._Colour;
		_PrevColour = other._PrevColour;
		_StartX = other._StartX;
		_CurrentY = other._CurrentY;
		_Width = other._Width;
		return *this;
	}

	void ConsoleProp::Init(int FontX, int FontY, int StartX, int StartY, unsigned short Colour, bool togFullscreen)
	{
		SetFont(FontX, FontY);
		SetColour(Colour);
		SetPrevColour(Colour);
		_Width = FindConsoleWidth();
		_StartX = StartX;
		_StartY = StartY;
		if (togFullscreen)
			ToggleFull();
	}

	int ConsoleProp::wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			return -1;
		return csbi.dwCursorPosition.X - _StartX;
	}

	int ConsoleProp::wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			return -1;
		return csbi.dwCursorPosition.Y;
	}

	void ConsoleProp::ToggleFull()
	{
		::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	}

	void ConsoleProp::RevertColour()
	{
		SetColour(_PrevColour);
	}

	void ConsoleProp::gotoxy(int x, int y)
	{
		COORD p = { static_cast<short>(x), static_cast<short>(y) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}

	void ConsoleProp::EndLine()
	{
		_CurrentY++;
		gotoxy(GetStartX(), _CurrentY);
	}

	void ConsoleProp::Update()
	{
		gotoxy(_StartX, _CurrentY);
		SetColour(_Colour);
	}

	//Getters
	int ConsoleProp::GetFontSize(HANDLE windowHandle, COORD *size)
	{
		CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };

		if (!GetCurrentConsoleFontEx(windowHandle, 0, &font))
			return 0;

		*size = font.dwFontSize;

		return 1;
	}

	int ConsoleProp::FindConsoleWidth()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			std::cerr << "Cannot determine console size." << std::endl;
		else
			return csbi.srWindow.Right - csbi.srWindow.Left + 1;
		return 0;
	}

	//Setters
	void ConsoleProp::SetFont(int FontX, int FontY)
	{
		_FontX = FontX;
		_FontY = FontY;
		UpdateFont();
	}

	void ConsoleProp::SetColour(unsigned short Colour)
	{
		_PrevColour = _Colour;
		_Colour = Colour;
		UpdateColour();
	}

	//Updates
	int ConsoleProp::UpdateFont()
	{
		HANDLE windowHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD size;

		if (GetFontSize(windowHandle, &size))
		{
			size.X = (SHORT)(size.X - size.X + _FontX);
			size.Y = (SHORT)(size.Y - size.Y + _FontY);

			CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };

			if (!GetCurrentConsoleFontEx(windowHandle, 0, &font))
				return 0;

			font.dwFontSize = size;

			if (!SetCurrentConsoleFontEx(windowHandle, 0, &font))
				return 0;

			return 1;
		}
		return 1;
	}

	void ConsoleProp::UpdateColour()
	{
		//Create handle
		HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
		//Set the colour with the handle and the passed Colour
		SetConsoleTextAttribute(hcon, _Colour);
	}
}