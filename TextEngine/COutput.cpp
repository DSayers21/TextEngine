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
				TypeString(TempVec[i], false);
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

	void COutput::WriteSlow(std::string DisplayString, bool EndL, bool CompLine)
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
				TypeString(TempVec[i], CompLine);
				if ((i != Size) && (_Console->wherex() != _Console->GetConsoleWidth()) && (_Console->wherex() != 0) && (_Console->wherex() != _Console->GetConsoleWidth() - 1))
					std::cout << " ";
			}
		}

		if (CompLine)
			CompleteLine(' ');

		if (EndL)
		{
			if (_Console->wherex() != _Console->GetStartX())
			{
				_Console->EndLine();
			}
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

	void COutput::TypeString(std::string DisplayString, bool CompLine)
	{
		int Size = static_cast<int>(DisplayString.size());
		int InitX = _Console->wherex();
		if (InitX + Size > _Console->GetConsoleWidth())
		{
			CompleteLine(' ');
			_Console->EndLine();
		}

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
		//Init LowestY
		int LowestY = 0;
		//Get console width
		int ColWidth = _Console->FindConsoleWidth()*0.333;
		//Create Columns to output information to
		TxtEgn::COutput _OutputLeft = CreateColumn(ColWidth, 0, Colour);
		TxtEgn::COutput _OutputMiddle = CreateColumn(ColWidth, ColWidth, Colour);
		TxtEgn::COutput _OutputRight = CreateColumn(ColWidth, ColWidth*2, Colour);
		//Output information to columns whilst updating lowestY
		LowestY = _OutputLeft.DisplayColumn(Left, LowestY);
		LowestY = _OutputMiddle.DisplayColumn(Middle, LowestY);
		LowestY = _OutputRight.DisplayColumn(Right, LowestY);
		//Set main console to the lowest position
		GetConsole()->SetCurrentY(++LowestY);
		GetConsole()->Update();
	}

	void COutput::DisplayColumnsConvo(std::string Left, std::string Right, int ColourA, int ColourB)
	{
		//Init LowestY
		int LowestY = 0;
		//Get console width
		int ColWidth = _Console->FindConsoleWidth()*0.333;
		//Create Columns to output information to
		TxtEgn::COutput _OutputLeft = CreateColumn(ColWidth, 0, ColourA);
		TxtEgn::COutput _OutputRight = CreateColumn(ColWidth*2+1, ColWidth, ColourB);
		//Output information to columns whilst updating lowestY
		LowestY = _OutputLeft.DisplayColumn(Left, LowestY);
		LowestY = _OutputRight.DisplayColumn(Right, LowestY);
		//Set main console to the lowest position
		GetConsole()->SetCurrentY(++LowestY);
		GetConsole()->Update();
	}

	COutput COutput::CreateColumn(int Width, int StartX, int Colour)
	{
		TxtEgn::ConsoleProp* _ConsoleCol = new TxtEgn::ConsoleProp();
		_ConsoleCol->Init(_Console->GetFontX(), _Console->GetFontY(), StartX, _Console->wherey(), Colour, false);
		_ConsoleCol->SetConsoleWidth(Width);
		_ConsoleCol->gotoxy(_ConsoleCol->GetStartX(), _ConsoleCol->GetStartY());

		TxtEgn::COutput _OutputCol(*_ConsoleCol, *_Input, *_Cache);
		return _OutputCol;
	}

	int COutput::DisplayColumn(std::string Statement, int LowestY)
	{
		GetConsole()->Update();
		WriteSlow(Statement, false, true);
		//CompleteLine(' ');
		return (GetConsole()->wherey() > LowestY) ? GetConsole()->GetCurrentY() : LowestY;
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