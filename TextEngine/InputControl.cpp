#include "InputControl.h"

#include <iostream>
#include <regex>
#include <iomanip>
#include <sstream>

namespace TxtEgn
{
	//Constructor
	InputControl::InputControl()
	{

	}

	//Destructor 
	InputControl::~InputControl()
	{

	}

	//Function to find where string is in vector
	int InputControl::ContainsString(std::vector<std::string> CheckVec, std::string ReadLine)
	{
		//Get size of vector
		int VecSizeTemp = static_cast<int>(CheckVec.size());
		//Loop through all of the elements in the vector
		for (int i = 0; i < VecSizeTemp; i++)
		{
			//Check if Compare is equal to ReadLine, if true return the position in the vector else continue
			if (CompareStrings(ReadLine, CheckVec[i]))
				return i;
		}//end for
		//Return -1 to show that the vector does not contain the string
		return -1;
	}

	//Function to break up the input into individual strings and stores them in a vector
	std::vector<std::string> InputControl::ParseIntoWords(std::string Current)
	{
		//Create vector to fill with strings
		std::vector<std::string> OutPut;
		//String Rem to store with the temp strings from input
		std::string Rem = "";
		//Set the Size to the size of the Current string
		int Size = static_cast<int>(Current.size());
		//Set char* Cur to equal the start of the Current String
		char* Cur = &Current[0];
		//Loop through all inputted letters
		for (int i = 0; i < Size; i++)
		{
			//Check if the current letter is not a space, if true then add the current letter to Rem
			if (Current[i] != ' ')
				Rem += Cur[i];
			//Check if the current letter is a space, or if its at the last character and Rem isn't null
			if (((Current[i] == ' ') || (Current[i] == '>') || (i == Size - 1))&(Rem != ""))
			{
				//Add Rem to the OutPut vector
				OutPut.push_back(Rem);
				//Set Rem back to being empty
				Rem = "";
			}//end if
		}//end for
		 //Return OutPut
		return OutPut;
	}

	//Function to ask input and return a vector of it
	std::vector<std::string> InputControl::AskInput()
	{
		//Input String
		std::string input;
		//Get input from user
		std::getline(std::cin, input);
		//Run the GetCommand function and pass the user entered string, and then return the result
		return ParseIntoWords(input);
	}

	//Function which takes multiple elements of vector and makes them a string
	std::string InputControl::ParseIntoSentence(std::vector<std::string> TempVector, int Start)
	{
		//Set Temp string to null
		std::string Temp = "";
		//Set the Size to the size of TempVector
		int VecSizeTemp = static_cast<int>(TempVector.size());
		//Loop trhough all the elements in the vector
		for (int x = Start; x < VecSizeTemp; x++)
		{
			//Check if x is == to the vector size -1, if true then add that element onto the end of temp, if not then do the same with a space added also
			(x == TempVector.size() - 1) ? Temp = Temp + TempVector[x] : Temp = Temp + TempVector[x] + " ";
		}//End loop
		 //Return Temp String
		return Temp;
	}

	//Function to count how want letters have been inputted
	int InputControl::HowManyLetters(char input[100])
	{
		//Set count to 0
		int Count = 0;
		//Loop through all the input
		for (int i = 0; i < 100; i++)
			if (input[i] != ' ') // Check if the current character is not a space, if true add one to count
				Count++;
		//Return Count
		return Count;
	}

	//Function to Check if a string is a number
	bool InputControl::is_number(std::string& s)
	{
		//Get size of vector
		int Size = static_cast<int>(s.size());
		//Loop through each character of string
		for (int i = 0; i < Size; i++)
			if (!isdigit(s[i])) //Check if the current character in string is not a digit
				return 0;
		return 1;
	}

	//Combines two strings together into one string
	std::string InputControl::CombineString(std::string StringA, std::string StringB)
	{
		//Create empty string
		std::string Temp = "";
		//Set first pass to true
		bool FirstPass = true;
		//Get size of string A
		int Size = static_cast<int>(StringA.size());
		//Create two characters to hold current values
		char Temp1, Temp2;
		//Check if both strings are the same size
		if (StringA.size() == StringB.size())
		{
			//Loop through every character in the string
			for (int i = 0; i < Size; i++)
			{
				//Set current characters to temp variables
				Temp1 = StringA[i];
				Temp2 = StringB[i];
				//Check if which of the temps are equal and not equal to ' ' and then add in the correct order
				if ((Temp1 == ' ') && (Temp2 != ' '))
					Temp = Temp + Temp2;
				else if ((Temp1 != ' ') && (Temp2 == ' '))
					Temp = Temp + Temp1;
				else
					Temp = Temp + ' ';   //Else just add space
			}
		}
		//Return
		return Temp;
	}

	//Finds if a string is located within an vector of strings
	bool InputControl::FindString(std::vector<std::string> CheckVec, std::string Search)
	{
		//Get size of vector of strings
		int VecSizeTemp = static_cast<int>(CheckVec.size());
		//Loop through all the strings in the vector
		for (int i = 0; i < VecSizeTemp; i++)
		{
			//Check if the current string in the vector is the same as the search criteria
			if (CompareStrings(Search, CheckVec[i]))
				return 1;
		}
		return 0;
	}

	//Finds the string position in a vector of strings
	int InputControl::FindStringPosition(std::vector<std::string> CheckVec, std::string Search)
	{
		//Get size of vector of strings
		int VecSizeTemp = static_cast<int>(CheckVec.size());
		//Loop through all the strings in the vector
		for (int i = 0; i < VecSizeTemp; i++)
		{
			//Check if the current string in the vector is the same as the search criteria
			if (CompareStrings(Search, CheckVec[i]))
				return i;	//Return current element
		}
		return -1;
	}

	//Compares two strings to see if they are the same
	bool InputControl::CompareStrings(std::string One, std::string Two)
	{
		//Transform both strings One and Two to being all lowercase
		std::transform(One.begin(), One.end(), One.begin(), ::tolower);
		std::transform(Two.begin(), Two.end(), Two.begin(), ::tolower);
		//Check if the two strings are the same then return true or false
		return  (One == Two) ? true : false;
	}

	//Function for Centering string on console
	std::string InputControl::AlignCenter(char Letter, int Buffer, std::string Original)
	{
		//Get size of Original string
		int TempN = static_cast<int>(Original.size());
		int TempN2 = static_cast<int>(Original.size());
		//Find how much to buffer each side
		TempN = (Buffer - TempN) / 2;
		//Add buffer to original string
		while (TempN2 != Buffer)
		{
			TempN2 = static_cast<int>(Original.size());
			if (TempN2 != Buffer)
				Original = Letter + Original;
			TempN2 = static_cast<int>(Original.size());
			if (TempN2 != Buffer)
				Original = Original + Letter;
		}
		//Return new string
		return Original;
	}

	//Function for Aligning left string on console
	std::string InputControl::AlignLeft(char Letter, int Buffer, std::string Original)
	{
		//Get size of Original string
		int TempN = static_cast<int>(Original.size());
		//Add buffer
		for (int i = TempN; i < Buffer; i++)
			Original = Original + Letter;
		//Return new string
		return Original;
	}

	//Function for Aligning right string on console
	std::string InputControl::AlignRight(char Letter, int Buffer, std::string Original)
	{
		//Get size of Original string
		int TempN = static_cast<int>(Original.size());
		//Add buffer
		for (int i = TempN; i < Buffer; i++)
			Original = Letter + Original;
		//Return new string
		return Original;
	}

	//Parses a string into a vector of ints by comma
	std::vector<int> InputControl::ParseByComma(std::string InputS)
	{
		//Create return vector
		std::vector<int> vect;
		//Create string to hold current level in return vector
		std::string rem = "";
		//Loop through all the characters in the input string
		for (int i = 0; i < InputS.size(); i++)
		{
			//Check if the current character is a space
			if ((InputS[i] == ' '))
			{}
			else
			{
				//Check if the current character is a comma
				if ((InputS[i] == ','))
				{
					//If true then push the current level to the vector and converit it to an int
					vect.push_back(stoi(rem));
					//Set back to "" to be repopulated by the next number inbetween commas
					rem = "";
				}
				else
					rem += InputS[i]; //Add the current character to the back of rem
			}
		}
		if(rem.size() > 0)
			vect.push_back(stoi(rem));
		
		//Return the populated vector of ints
		return vect;
	}

	//Removes all the spaces in a string
	std::string InputControl::RemoveSpaces(std::string Original)
	{
		//Create return vector
		std::string Out = "";
		//Loop through each character in the input string
		for (int i = 0; i < Original.size(); i++)
		{
			//If the current character is not a space then add it to the output string
			if (Original[i] != ' ')
				Out += Original[i];
		}
		//Return the vector
		return Out;
	}
}