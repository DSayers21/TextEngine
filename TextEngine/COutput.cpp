#include "COutput.h"
#include "InputControl.h"
#include "Pixel.h"

#include <chrono>
#include <thread>

namespace TxtEgn
{
	COutput::COutput() : _Speed(10)
	{
	}

	COutput::COutput(ConsoleProp& Console, InputControl& Input, ImageCache& Cache) :
		_Console(&Console),
		_Input(&Input),
		_Cache(&Cache),
		_Speed(0)
	{

	}

	COutput::~COutput()
	{
	}

	void COutput::DisplayBanner(int Colour, std::string Statement, bool EndL)
	{
		_Console->SetColour(Colour);
		//Run WriteSlow Function
		std::cout << Statement;
		if (EndL)
			_Console->EndLine();
		_Console->SetColour(_Console->GetPrevColour());
	}

	void COutput::WriteSlow(std::string DisplayString, bool EndL)
	{
		std::vector<std::string> TempVec = _Input->ParseIntoWords(DisplayString);
		int Size = static_cast<int>(TempVec.size());
		for (int i = 0; i < Size; i++)
		{
			if ((TempVec[i].size() > 3) && (TestTag(TempVec[i]) == 2))
			{
				_Console->RevertColour();
			}
			else if ((TempVec[i].size() > 3) && (TestTag(TempVec[i]) == 1))
				SetTag(TempVec[i]);
			else
			{
				TypeString(TempVec[i]);
				if ((i != Size) && (_Console->wherex() != _Console->GetConsoleWidth()) && (_Console->wherex() != 0) && (_Console->wherex() != _Console->GetConsoleWidth() - 1))
					std::cout << " ";
			}
		}
		if (EndL)
		{
			if(_Console->wherex() != _Console->GetStartX())
				_Console->EndLine();
		}
	}

	//Write a line of characters across the screen
	void COutput::WriteLine(int Colour, char WriteChar)
	{
		//Set Colour to the colour passed to the function
		_Console->SetColour(Colour);
		//Go through each char space on screen and place char there
		for (int i = _Console->GetStartX(); i < _Console->GetConsoleWidth(); i++)
		{
			std::cout << WriteChar;
		}
		_Console->EndLine();
	}

	void COutput::CompleteLine(char FinChar)
	{
		int Buffer = _Console->GetConsoleWidth();
		int CurPos = _Console->wherex();

		for (int i = CurPos; i < Buffer; i++)
			std::cout << FinChar;
	}

	void COutput::DisplayTextBox(std::vector<std::string> SentText, char Surround, int Colour)
	{
		int VecSize = static_cast<int>(SentText.size());
		std::string Space = "";
		std::string LEndCap = _Input->AlignLeft(' ', _Console->GetConsoleWidth(), Space + Surround);
		std::string REndCap = _Input->AlignRight(' ', _Console->GetConsoleWidth(), Surround + Space);
		std::string Output;

		WriteLine(Colour, Surround);
		for (int i = 0; i < VecSize; i++)
		{
			Output = _Input->CombineString(LEndCap, REndCap);
			Output = _Input->CombineString(Output, _Input->AlignCenter(' ', _Console->GetConsoleWidth(), SentText[i]));
			DisplayBanner(Colour, Output, false);
		}
		WriteLine(Colour, Surround);
	}

	void COutput::ConsoleClear()
	{
		int PrevY = _Console->wherey();
		_Console->SetCurrentY(_Console->GetStartY());
		_Console->gotoxy(_Console->GetStartX(), _Console->GetStartY());
		for (int i = _Console->GetStartY(); i <= PrevY; i++)
		{
			WriteLine(0, ' ');
			_Console->gotoxy(_Console->GetStartX(), i);
		}
		_Console->gotoxy(_Console->GetStartX(), _Console->GetStartY());

	}

	std::vector<std::string> COutput::GetInput(std::string Question)
	{
		unsigned short TmpCol = _Console->GetColour();
		unsigned short PTmpCol = _Console->GetPrevColour();
		WriteSlow("<C10>" + Question + " <C7> " + ">", false);
		std::vector<std::string> InData = _Input->AskInput();
		_Console->EndLine();
		_Console->SetColour(TmpCol);
		_Console->SetPrevColour(PTmpCol);
		return InData;
	}

	void COutput::DrawImage(std::string Img, ALIGN Align)
	{
		//Get image from cache
		std::vector<Pixel> Image;
		ASCImage& AImg = _Cache->GetTexture(Img);
		Image = AImg.GetImage();

		int OFFx = ImageAlign(AImg, Align);

		int Width = AImg.GetWidth();

		//Display
		if (_Console->wherex() != _Console->GetStartX() + OFFx)
		{
			_Console->SetCurrentY(_Console->GetCurrentY() + 1);
			_Console->gotoxy(_Console->GetStartX(), _Console->GetCurrentY());
		}
		_Console->gotoxy(OFFx, _Console->GetCurrentY());

		int Count = _Console->GetStartX();

		for (int i = 0; i < Image.size(); i++)
		{
			_Console->SetColour(Image[i].GetColour());
			std::cout << Image[i].GetChar() << Image[i].GetChar();
			//std::this_thread::sleep_for(std::chrono::milliseconds(4));
			if (Count == Width - 1)
			{
				//Show Line
				_Console->EndLine();
				_Console->gotoxy(OFFx, _Console->GetCurrentY());
				Count = 0;
			}
			else
				Count++;
		}
		_Console->SetCurrentY(_Console->GetCurrentY() + 1);
		_Console->gotoxy(_Console->GetStartX(), _Console->GetCurrentY());
	}

	bool COutput::CheckIfOver(std::string DisplayString)
	{
		int TempSize = static_cast<int>(DisplayString.size());
		if (TempSize == _Console->GetConsoleWidth())
		{
			char First = DisplayString[0];
			char Last = DisplayString[TempSize - 1];

			if ((First == ' ') || (Last == ' '))
				return true;
		}
		return false;
	}

	void COutput::TypeString(std::string DisplayString)
	{
		int Size = static_cast<int>(DisplayString.size());
		int InitX = _Console->wherex();
		if (InitX + Size > _Console->GetConsoleWidth())
			_Console->EndLine();

		for (int i = 0; i < Size; i++)
		{
			std::cout << DisplayString[i];
			std::this_thread::sleep_for(std::chrono::milliseconds(_Speed));
		}
		if (InitX + Size == _Console->GetConsoleWidth())
			_Console->EndLine();
	}

	int COutput::TestTag(std::string StringPassed)
	{
		char First, Second, Last, Special;
		int Size = static_cast<int>(StringPassed.size());

		First = StringPassed[0];
		Second = StringPassed[1];
		Special = StringPassed[2];
		Last = StringPassed[Size - 1];

		if ((First == '<') && (Second == 'C') && (Special == '/') && (Last == '>'))
			return 2;
		if ((First == '<') && (Second == 'C') && (Last == '>'))
			return 1;
		return 0;
	}

	void COutput::SetTag(std::string StringPassed)
	{
		int Size = static_cast<int>(StringPassed.size());
		std::string TagNum = "";

		for (int i = 0; i < Size; i++)
			if (isdigit(StringPassed[i]))
				TagNum = TagNum + StringPassed[i];
		_Console->SetColour(std::stoi(TagNum));
	}

	int COutput::ImageAlign(ASCImage Img, ALIGN Align)
	{
		switch (Align)
		{
		case ALIGN::LEFT:
			return 0;
			break;
		case ALIGN::CENTER:
			return ((_Console->GetConsoleWidth()) - Img.GetWidth() * 2) / 2;
			break;
		case ALIGN::RIGHT:
			return ((_Console->GetConsoleWidth() - Img.GetWidth() * 2));
			break;
		}
	}

	void COutput::DisplayColumns3(std::string Left, std::string Middle, std::string Right, int Colour)
	{
		int LowestY = 0;

		int SecLeft = _Console->FindConsoleWidth()*0.333;

		TxtEgn::ConsoleProp _ConsoleLeft;
		_ConsoleLeft.Init(10, 16, 0, _Console->wherey(), Colour, false);
		_ConsoleLeft.SetConsoleWidth(SecLeft);
		_ConsoleLeft.gotoxy(_ConsoleLeft.GetStartX(), _ConsoleLeft.GetStartY());

		TxtEgn::COutput _OutputLeft(_ConsoleLeft, *_Input, *_Cache);

		TxtEgn::ConsoleProp _ConsoleMiddle;
		_ConsoleMiddle.Init(10, 16, SecLeft, _Console->wherey(), Colour, false);
		_ConsoleMiddle.SetConsoleWidth(SecLeft);
		_ConsoleMiddle.gotoxy(_ConsoleLeft.GetStartX(), _ConsoleLeft.GetStartY());

		TxtEgn::COutput _OutputMiddle(_ConsoleMiddle, *_Input, *_Cache);

		TxtEgn::ConsoleProp _ConsoleRight;
		_ConsoleRight.Init(10, 16, SecLeft*2, _Console->wherey(), Colour, false);
		_ConsoleRight.SetConsoleWidth(SecLeft);
		_ConsoleRight.gotoxy(_ConsoleLeft.GetStartX(), _ConsoleLeft.GetStartY());

		TxtEgn::COutput _OutputRight(_ConsoleRight, *_Input, *_Cache);

		_OutputLeft.GetConsole()->Update();
		_OutputLeft.WriteSlow(Left, false);
		_OutputLeft.CompleteLine(' ');
		LowestY = _OutputLeft.GetConsole()->wherey();

		_OutputMiddle.GetConsole()->Update();
		_OutputMiddle.WriteSlow(Middle, false);
		_OutputMiddle.CompleteLine(' ');
		LowestY = (_OutputMiddle.GetConsole()->wherey() > LowestY) ? _OutputLeft.GetConsole()->wherey() : LowestY;

		_OutputRight.GetConsole()->Update();
		_OutputRight.WriteSlow(Right, false);
		_OutputRight.CompleteLine(' ');
		_OutputRight.GetConsole()->EndLine();
		LowestY = (_OutputRight.GetConsole()->wherey() > LowestY) ? _OutputLeft.GetConsole()->wherey() : LowestY;

		GetConsole()->SetCurrentY(LowestY);
	}

	//Setters
	void COutput::SetConsole(ConsoleProp& Console)
	{
		_Console = &Console;
	}

	void COutput::SetInput(InputControl& Input)
	{
		_Input = &Input;
	}

	//Getters
	ConsoleProp* COutput::GetConsole()
	{
		return _Console;
	}
}