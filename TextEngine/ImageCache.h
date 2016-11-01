#pragma once

//Includes
#include <vector>
#include <string>
#include <map>
#include "Pixel.h"
#include "InputControl.h"
#include "ASCImage.h"

namespace TxtEgn
{
	class InputControl;

	class ImageCache
	{
	public:
		//Constructor
		ImageCache();
		//Constructor with passed InputControl
		ImageCache(InputControl& Input);
		//Destructor
		~ImageCache();
		//Trys to find a image in the cache if it cant then it loads it into the cache and then returns it
		ASCImage GetTexture(std::string FileName);

	private:
		//Loads an image with a given filename
		ASCImage LoadImage(std::string FileName);
		//Converts image from a vector of ints to a vector of Pixels
		std::vector<Pixel> ConvertImage(std::vector<int> SentImage);

		//Member variables
		//map of images against their filenames
		std::map<std::string, ASCImage> _ImageMap;
		//InputControl which this interfaces with
		InputControl* _Input;
	};
}