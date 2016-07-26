#include "COutput.h"
#include "InputControl.h"

#include <chrono>
#include <thread>

COutput::COutput() : _Speed(10)
{
}

COutput::COutput(ConsoleProp& Console, InputControl& Input) : _Console(&Console), _Input(&Input), _Speed(0)
{

}

COutput::~COutput()
{
}

void COutput::DisplayBanner(int Colour, std::string Statement, bool EndL)
{
	_Console->Update();
	//Run WriteSlow Function
	std::cout << Statement;
	if (EndL)
		_Console->EndLine();
}

void COutput::WriteSlow(std::string DisplayString, bool EndL)
{
	_Console->Update();
	std::vector<std::string> TempVec = _Input->ParseIntoWords(DisplayString);
	int Size = static_cast<int>(TempVec.size());
	for (int i = 0; i < Size; i++)
		if ((TempVec[i].size() > 3) && (TestTag(TempVec[i])))
			SetTag(TempVec[i]);
		else
		{
			TypeString(TempVec[i]);
			if ((i != Size) && (_Console->wherex() != _Console->GetConsoleWidth()) && (_Console->wherex() != 0) && (_Console->wherex() != _Console->GetConsoleWidth() - 1))
				std::cout << " ";
		}

	if (EndL)
		_Console->EndLine();
}

//Write a line of characters across the screen
void COutput::WriteLine(int Colour, char WriteChar)
{
	_Console->Update();
	//Set Colour to the colour passed to the function
	_Console->SetColour(Colour);
	//Go through each char space on screen and place char there
	for (int i = _Console->GetStartX() - _Console->GetConsoleWidth(); i < _Console->GetConsoleWidth(); i++)
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
	int PrevY = _Console->GetCurrentY();
	_Console->SetCurrentY(_Console->GetStartY());
	_Console->gotoxy(_Console->GetStartX(), _Console->GetStartY());
	for (int i = _Console->GetStartY(); i < PrevY; i++)
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

	if (_Console->wherex() + Size > _Console->GetConsoleWidth())
		_Console->EndLine();

	for (int i = 0; i < Size; i++)
	{
		std::cout << DisplayString[i];
		std::this_thread::sleep_for(std::chrono::milliseconds(_Speed));
	}
}

bool COutput::TestTag(std::string StringPassed)
{
	char First, Second, Last;
	int Size = static_cast<int>(StringPassed.size());

	First = StringPassed[0];
	Second = StringPassed[1];
	Last = StringPassed[Size - 1];

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