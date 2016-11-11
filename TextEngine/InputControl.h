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
		//Returns how many letters that are im a 100 character input
		int HowManyLetters(char input[100]);
		//Checks if a string is a number
		bool is_number(std::string& s);
		//Combines two strings together
		std::string CombineString(std::string Combi1, std::string Combi2);
		//Finds if a string is located in a vector of strings
		bool FindString(std::vector<std::string> CheckVec, std::string Search);
		//Gets the location of a string inside of a vector of strings
		int FindStringPosition(std::vector<std::string> CheckVec, std::string Search);
		//Compares two strings and says if they are 
		bool CompareStrings(std::string One, std::string Two);
		//Aligns a string to the center
		std::string AlignCenter(char Letter, int Buffer, std::string Original);
		//Aligns a string to the left
		std::string AlignLeft(char Letter, int Buffer, std::string Original);
		//Aligns a string to the right
		std::string AlignRight(char Letter, int Buffer, std::string Original);
		//Parses a input string by commas and returns a vector of ints
		std::vector<int> ParseByComma(std::string InputS);
		//Removes all spaces in a string
		std::string RemoveSpaces(std::string Original);
	};
}