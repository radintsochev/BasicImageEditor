#pragma once
#include "Command.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"


class MonochromePPM : public Command<PPMImage> {
public:
	void apply(PPMImage& image) override {
		for (size_t i = 0; i < image.getDataLength() / 3; i++)
		{
			if (!(image.getData())[i].isGray())
			{
				(image.getData())[i].grayscale();
				if (!((image.getData())[i].red == 0 || (image.getData())[i].red == image.getMaxValue()))
				{
					if ((image.getData())[i].red > image.getMaxValue() / 2)
					{
						(image.getData())[i].red = image.getMaxValue();
						(image.getData())[i].green = image.getMaxValue();
						(image.getData())[i].blue = image.getMaxValue();
					}
					else
					{
						(image.getData())[i].red = 0;
						(image.getData())[i].green = 0;
						(image.getData())[i].blue = 0;
					}
				}
			}
			else if (!((image.getData())[i].red == 0 || (image.getData())[i].red == image.getMaxValue()))
			{
				if ((image.getData())[i].red > image.getMaxValue() / 2)
				{
					(image.getData())[i].red = image.getMaxValue();
					(image.getData())[i].green = image.getMaxValue();
					(image.getData())[i].blue = image.getMaxValue();
				}
				else
				{
					(image.getData())[i].red = 0;
					(image.getData())[i].green = 0;
					(image.getData())[i].blue = 0;
				}
			}
		}
	}
};

class MonochromePGM : public Command<PGMImage> {
public:
	void apply(PGMImage& image) override {
		for (size_t i = 0; i < image.getDataLength(); i++)
		{
			if (!((image.getData())[i] == 0 || (image.getData())[i] == image.getMaxValue()))
			{
				if ((image.getData())[i] > image.getMaxValue() / 2)
				{
					(image.getData())[i] = image.getMaxValue();
				}
				else
				{
					(image.getData())[i] = 0;
				}
			}
		}
	}
};

class MonochromePBM : public Command<PBMImage> {
public:
	void apply(PBMImage& image) override {}
};