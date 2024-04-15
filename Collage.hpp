#pragma once
#include "Command.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"
#include "Rotate.hpp"

class CollagePPM : public Command<PPMImage> {
public:
	void apply(const char* direction, PPMImage& firstImage, PPMImage& secondImage, const char* outImageName) override {
		if (strcmp(direction, "horizontal") != 0 && strcmp(direction, "vertical") != 0)
		{
			throw std::runtime_error("Invalid direction!");
		}
		PPMImage outImage;
		if (firstImage.getHeight() == secondImage.getHeight() && firstImage.getWidth() == secondImage.getWidth() && firstImage.getType() == secondImage.getType())
		{
			if (!strcmp(direction, "horizontal"))
			{
				RotatePPM rotate;
				rotate.apply("right", firstImage);
				rotate.apply("right", secondImage);
			}

			outImage.setType(firstImage.getType());
			outImage.setWidth(firstImage.getWidth());
			outImage.setHeight((firstImage.getHeight()) * 2);
			outImage.setMaxValue(firstImage.getMaxValue());
			outImage.setDataLength(outImage.getHeight() * outImage.getWidth());
			RGBPixel* newData = new RGBPixel[outImage.getDataLength()];
			for (size_t i = 0, j = 0, k = 0; i < outImage.getDataLength(); i++)
			{
				if (j < outImage.getDataLength() / 2)
				{
					newData[i] = (firstImage.getData())[j];
					j++;
				}
				else
				{
					newData[i] = (secondImage.getData())[k];
					k++;
				}
			}
			outImage.setData(newData);

				RotatePPM rotate;
				rotate.apply("left", outImage);

			if (!strcmp(direction, "vertical"))
			{
				RotatePPM rotate;
				rotate.apply("right", outImage);
			}

			std::ofstream imageFileOut2(outImageName, std::ios::binary | std::ios::out);
			if (!imageFileOut2.is_open())
			{
				throw std::runtime_error("File did not open!");
			}

			outImage.save(imageFileOut2);
			if (!strcmp(direction, "horizontal"))
			{
				RotatePPM rotate;
				rotate.apply("left", firstImage);
				rotate.apply("left", secondImage);
			}

		}
	}
};


class CollagePGM : public Command<PGMImage> {
public:
	void apply(const char* direction, PGMImage& firstImage, PGMImage& secondImage, const char* outImageName) override {
		if (strcmp(direction, "horizontal") != 0 && strcmp(direction, "vertical") != 0)
		{
			throw std::runtime_error("Invalid direction!");
		}
		PGMImage outImage;
		if (firstImage.getHeight() == secondImage.getHeight() && firstImage.getWidth() == secondImage.getWidth() && firstImage.getType() == secondImage.getType())
		{
			if (!strcmp(direction, "horizontal"))
			{
				RotatePGM rotate;
				rotate.apply("right", firstImage);
				rotate.apply("right", secondImage);
			}
			
				outImage.setType(firstImage.getType());
				outImage.setWidth(firstImage.getWidth());
				outImage.setHeight((firstImage.getHeight()) * 2);
				outImage.setMaxValue(firstImage.getMaxValue());
				outImage.setDataLength(outImage.getHeight() * outImage.getWidth());
				int* newData = new int[outImage.getDataLength()];
				for (size_t i = 0, j = 0, k = 0; i < outImage.getDataLength(); i++)
				{
					if (j < outImage.getDataLength() / 2)
					{
						newData[i] = (firstImage.getData())[j];
						j++;
					}
					else
					{
						newData[i] = (secondImage.getData())[k];
						k++;
					}
				}
				outImage.setData(newData);
				
				RotatePGM rotate;
				rotate.apply("left", outImage);
			
				if (!strcmp(direction, "vertical"))
				{
					RotatePGM rotate;
					rotate.apply("right", outImage);
				}

				std::ofstream imageFileOut2(outImageName, std::ios::binary | std::ios::out);
				if (!imageFileOut2.is_open())
				{
					throw std::runtime_error("File did not open!");
				}

				outImage.save(imageFileOut2);
				if (!strcmp(direction, "horizontal"))
				{
					RotatePGM rotate;
					rotate.apply("left", firstImage);
					rotate.apply("left", secondImage);
				}
			
		}
	}
};


class CollagePBM : public Command<PBMImage> {
public:
	void apply(const char* direction, PBMImage& firstImage, PBMImage& secondImage, const char* outImageName) override {
		if (strcmp(direction, "horizontal") != 0 && strcmp(direction, "vertical") != 0)
		{
			throw std::runtime_error("Invalid direction!");
		}
		PBMImage outImage;
		if (firstImage.getHeight() == secondImage.getHeight() && firstImage.getWidth() == secondImage.getWidth() && firstImage.getType() == secondImage.getType())
		{
			if (!strcmp(direction, "horizontal"))
			{
				RotatePBM rotate;
				rotate.apply("right", firstImage);
				rotate.apply("right", secondImage);
			}

			outImage.setType(firstImage.getType());
			outImage.setWidth(firstImage.getWidth());
			outImage.setHeight((firstImage.getHeight()) * 2);
			outImage.setMaxValue(firstImage.getMaxValue());
			outImage.setDataLength(outImage.getHeight() * outImage.getWidth());
			bool* newData = new bool[outImage.getDataLength()];
			for (size_t i = 0, j = 0, k = 0; i < outImage.getDataLength(); i++)
			{
				if (j < outImage.getDataLength() / 2)
				{
					newData[i] = (firstImage.getData())[j];
					j++;
				}
				else
				{
					newData[i] = (secondImage.getData())[k];
					k++;
				}
			}
			outImage.setData(newData);

			RotatePBM rotate;
			rotate.apply("left", outImage);

			if (!strcmp(direction, "vertical"))
			{
				RotatePBM rotate;
				rotate.apply("right", outImage);
			}

			std::ofstream imageFileOut2(outImageName, std::ios::binary | std::ios::out);
			if (!imageFileOut2.is_open())
			{
				throw std::runtime_error("File did not open!");
			}

			outImage.save(imageFileOut2);
			if (!strcmp(direction, "horizontal"))
			{
				RotatePBM rotate;
				rotate.apply("left", firstImage);
				rotate.apply("left", secondImage);
			}

		}
	}
};