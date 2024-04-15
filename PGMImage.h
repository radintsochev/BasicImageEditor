#pragma once
#include "PNMImage.h"

class PGMImage : public PNMImage {
private:
	int* data = nullptr;
	PGMImage* last = nullptr;
public:
	PGMImage() = default;
	PGMImage(const PGMImage& other);
	PGMImage& operator=(const PGMImage& other);

	void setData(const int* data);
	int* getData() const { return data; }
	PGMImage* getLast() const { return last; }
	void setLast(PGMImage* last) { this->last = last; }

	char* load(std::ifstream& imageFile);
	void save(std::ofstream& imageFile) const;

	PGMImage* clone() const;

	~PGMImage();
private:
	void free();
};