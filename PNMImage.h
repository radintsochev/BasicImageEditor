#pragma once
#include "Image.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

#pragma warning(disable : 4996)

class PNMImage  : public Image {
protected:
	int type = 1;
	int width = 0;
	int height = 0;
	int maxValue = 0;
	int dataLength = 0;
public:
	void setType(const int type);
	void setWidth(const int width);
	void setHeight(const int height);
	void setMaxValue(const int maxValue);
	void setDataLength(const int dataLength);

	int getType() const;
	int getWidth() const;
	int getHeight() const;
	int getMaxValue() const;
	int getDataLength() const;

	char* load(std::ifstream& imageFile) override;
	void save(std::ofstream& imageFile) const override;
};