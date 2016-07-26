#pragma once

#include <string>
#include <vector>
#include "ConsoleProp.h"

namespace TxtEgn
{
	class InputControl
	{
	public:
		InputControl();

		~InputControl();

		int ContainsString(std::vector<std::string> CheckVec, std::string ReadLine);

		std::vector<std::string> ParseIntoWords(std::string Current);

		std::vector<std::string> AskInput();

		std::string ParseIntoSentence(std::vector<std::string> TempVector, int Start);

		int HowManyLetters(char input[100]);

		bool is_number(std::string& s);

		std::string CombineString(std::string Combi1, std::string Combi2);

		bool FindString(std::vector<std::string> CheckVec, std::string Search);

		bool CompareStrings(std::string One, std::string Two);

		std::string AlignCenter(char Letter, int Buffer, std::string Original);

		std::string AlignLeft(char Letter, int Buffer, std::string Original);

		std::string AlignRight(char Letter, int Buffer, std::string Original);

		std::vector<int> ParseByComma(std::string InputS);
	};
}