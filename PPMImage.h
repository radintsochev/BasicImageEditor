#pragma once
#include "PNMImage.h"

struct RGBPixel {
	int red = 0;
	int green = 0;
	int blue = 0;

	bool isGray() {
		return red == green && green == blue;
	}

	void grayscale() {
		double gray = (double)red * 0.2126 + (double)green * 0.7152 + (double)blue * 0.0722;
		red = (int)gray;
		green = (int)gray;
		blue = (int)gray;
	}

};

class PPMImage : public PNMImage {
private:
	RGBPixel* data = nullptr;
	PPMImage* last = nullptr;
public:
	PPMImage() = default;
	PPMImage(const PPMImage& other);
	PPMImage& operator=(const PPMImage& other);

	void setData(const RGBPixel* data);
	RGBPixel* getData() const { return data; }
	PPMImage* getLast() const { return last; }
	void setLast(PPMImage* last) { this->last = last; }

	char* load(std::ifstream& imageFile);
	void save(std::ofstream& imageFile) const;

	PPMImage* clone() const;

	~PPMImage();
private:
	void free();
};