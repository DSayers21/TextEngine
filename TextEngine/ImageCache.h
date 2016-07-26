#pragma once

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
		ImageCache(InputControl& Input);

		~ImageCache();

		ASCImage GetTexture(std::string FileName);

	private:
		ASCImage LoadImage(std::string FileName);

		std::vector<Pixel> ConvertImage(std::vector<int> SentImage);

		std::map<std::string, ASCImage> _ImageMap;

		InputControl* _Input;
	};
}