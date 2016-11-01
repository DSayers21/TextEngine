#pragma once

//Includes
#include <vector>
#include <string>
#include <map>
#include "Pixel.h"

namespace TxtEgn
{
	class ASCImage
	{
	public:
		//Base Constructor
		ASCImage()
		{
			//Empty
		}

		//Main Constructor
		ASCImage(std::vector<Pixel> Img, int Width) : _Image(Img), _Width(Width)
		{	
			//Empty
		}

		//Destructor
		~ASCImage()
		{
			//Empty
		}

		//Copy Constructor
		ASCImage(const ASCImage& other)
		{
			_Image = other._Image;
			_Width = other._Width;

		}

		//Equal operator
		ASCImage operator=(const ASCImage &other)
		{
			_Image = other._Image;
			_Width = other._Width;
			return *this;
		}

		//Init function
		void Init(std::vector<Pixel>& Img, int Width)
		{
			_Image = Img;
			_Width = Width;
		}

		//Getters
		std::vector<Pixel> GetImage() { return _Image; }	//Returns the image
		int GetWidth() { return _Width; }					//Returns the Width of the image

	private:
		//The image
		std::vector<Pixel> _Image;
		//Width of the image
		int _Width;
	};
}