#include "ImageCache.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdio.h>

namespace TxtEgn
{
	ImageCache::ImageCache()
	{

	}

	ImageCache::ImageCache(InputControl& Input)
	{
		_Input = &Input;
	}


	ImageCache::~ImageCache()
	{
	}

	ASCImage ImageCache::GetTexture(std::string FileName)
	{
		//Lookup the texture and see if its in the map
		auto Mit = _ImageMap.find(FileName);
		//Check if its not in the map
		if (Mit == _ImageMap.end())
		{
			//Load Texture
			ASCImage NewImage = LoadImage(FileName);
			//Insert into map
			_ImageMap.insert(make_pair(FileName, NewImage));
			OutputDebugString(L"Loaded Texture");

			int Size = NewImage.GetImage().size();

			return NewImage;
		}
		OutputDebugString(L"Used Catched Texture");
		return Mit->second;
	}

	ASCImage ImageCache::LoadImage(std::string FileName)
	{
		std::string Input, Line;
		std::ifstream myfile(FileName);

		int Count = 0;
		int Width;
		if (myfile.is_open())
		{
			while (getline(myfile, Line))
			{
				if (Count == 0)
				{
					if (_Input->is_number(Line))
						Width = stoi(Line);
					Count++;
				}
				else
					Input = Line;
			}
			myfile.close();

			std::vector<int> Temp = _Input->ParseByComma(Input);
			std::vector<Pixel> Img = ConvertImage(Temp);
			ASCImage TImg(Img, Width);

			return TImg;
		}
		else std::cout << "Unable to open file" << std::endl;
	}

	std::vector<Pixel> ImageCache::ConvertImage(std::vector<int> SentImage)
	{
		std::vector<Pixel> ConImg;
		for (int i = 0; i < SentImage.size(); i++)
		{
			Pixel newPix(SentImage[i]);
			//std::cout << newPix.GetColour();

			ConImg.push_back(newPix);
		}
		return ConImg;
	}
}