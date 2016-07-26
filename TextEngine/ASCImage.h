#pragma once

#include <vector>
#include <string>
#include <map>
#include "Pixel.h"

namespace TxtEgn
{
	class ASCImage
	{
	public:
		ASCImage()
		{

		}

		ASCImage(std::vector<Pixel> Img, int Width) : _Image(Img), _Width(Width)
		{

		}

		~ASCImage()
		{

		}

		ASCImage(const ASCImage& other)
		{
			_Image = other._Image;
			_Width = other._Width;

		}
		ASCImage operator=(const ASCImage &other)
		{
			_Image = other._Image;
			_Width = other._Width;
			return *this;
		}

		void Init(std::vector<Pixel>& Img, int Width)
		{
			_Image = Img;
			_Width = Width;
		}
		//Getters
		std::vector<Pixel> GetImage() { return _Image; }

		int GetWidth() { return _Width; }

	private:
		std::vector<Pixel> _Image;
		int _Width;
	};
}