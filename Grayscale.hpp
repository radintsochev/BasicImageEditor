#pragma once
#include "Command.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"


class GrayscalePPM : public Command<PPMImage> {
public:
	void apply(PPMImage& image) override {
		for (size_t i = 0; i < image.getDataLength() / 3; i++)
		{
			if (!(image.getData())[i].isGray())
			{
				(image.getData())[i].grayscale();
			}
		}
	}
};

class GrayscalePGM : public Command<PGMImage> {
public:
	void apply(PGMImage& image) override {}
};

class GrayscalePBM : public Command<PBMImage> {
public:
	void apply(PBMImage& image) override {}
};