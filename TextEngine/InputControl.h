#pragma once

//Includes
#include <string>
#include <vector>
#include "ConsoleProp.h"

namespace TxtEgn
{
	class InputControl
	{
	public:
		//Constructor
		InputControl();
		//Destructor
		~InputControl();
		//Checks if vector of strings contains a string, returns its position in that vector
		int ContainsString(std::vector<std::string> CheckVec, std::string ReadLine);
		//Splits a string up by "spaces"
		std::vector<std::string> ParseIntoWords(std::string Current);
		//Gets user input from the console, returns as a vector of strings
		std::vector<std::string> AskInput();
		//Takes a vector of strings and combines the strings in it after a start positon in the vector
		std::string ParseIntoSentence(std::vector<std::string> TempVector, int Start);

		int HowManyLetters(char input[100]);

		bool is_number(std::string& s);

		std::string CombineString(std::string Combi1, std::string Combi2);

		bool FindString(std::vector<std::string> CheckVec, std::string Search);

		int FindStringPosition(std::vector<std::string> CheckVec, std::string Search);

		bool CompareStrings(std::string One, std::string Two);

		std::string AlignCenter(char Letter, int Buffer, std::string Original);

		std::string AlignLeft(char Letter, int Buffer, std::string Original);

		std::string AlignRight(char Letter, int Buffer, std::string Original);

		std::vector<int> ParseByComma(std::string InputS);

		int SearchVector(std::vector<std::string> Vector, std::string Find);

		std::string RemoveSpaces(std::string Original);
	};
}