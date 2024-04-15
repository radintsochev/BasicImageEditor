#pragma once
#include "Command.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"


class NegativePPM : public Command<PPMImage> {
public:
	void apply(PPMImage& image) override {
		for (size_t i = 0; i < image.getDataLength() / 3; i++)
		{
			(image.getData())[i].red = image.getMaxValue() - (image.getData())[i].red;
			(image.getData())[i].green = image.getMaxValue() - (image.getData())[i].green;
			(image.getData())[i].blue = image.getMaxValue() - (image.getData())[i].blue;
		}
	}
};

class NegativePGM : public Command<PGMImage> {
public:
	void apply(PGMImage& image) override {
		for (size_t i = 0; i < image.getDataLength(); i++)
		{
			(image.getData())[i] = image.getMaxValue() - (image.getData())[i];
		}
	}
};

class NegativePBM : public Command<PBMImage> {
public:
	void apply(PBMImage& image) override {
		for (size_t i = 0; i < image.getDataLength(); i++)
		{
			(image.getData())[i] = !((image.getData())[i]);
		}
	}
};