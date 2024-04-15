#pragma once
#include "PNMImage.h"

class PBMImage : public PNMImage{
private:
	bool* data = nullptr;
public:
	PBMImage() = default;
	PBMImage(const PBMImage& other);
	PBMImage& operator=(const PBMImage& other);

	void setData(const bool* data);
	bool* getData() const { return data; }

	char* load(std::ifstream& imageFile);
	void save(std::ofstream& imageFile) const;

	~PBMImage();
private:
	void free();
};