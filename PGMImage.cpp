#include "PGMImage.h"

PGMImage::PGMImage(const PGMImage& other) : PNMImage(other) {
	setData(other.data);
}

PGMImage& PGMImage::operator=(const PGMImage& other) {
	if (this != &other)
	{
		PNMImage::operator=(other);
		last = other.last;
		setData(other.data);
	}
	return *this;
}

void PGMImage::setData(const int* data) {
	this->data = new int[dataLength];
	for (size_t i = 0; i < dataLength; i++)
	{
		this->data[i] = data[i];
	}
}

char* PGMImage::load(std::ifstream& imageFile) {
	char* fileData = PNMImage::load(imageFile);

	//Set the image data:
	int* data = new int[this->dataLength];
	int i = 0;
	while (i != dataLength)
	{
		while (fileData[i] == '\0')
		{
			i++;
		}
		data[i] = (int)((unsigned char)fileData[i]);
		i++;
	}
	setData(data);

	delete[] fileData;
	return nullptr;
}

void PGMImage::save(std::ofstream& imageFile) const {
	PNMImage::save(imageFile);

	for (size_t i = 0; i < dataLength; i++)
	{
		imageFile.put((char)data[i]);
	}

	imageFile.close();
}

PGMImage::~PGMImage() {
	free();
}

void PGMImage::free() {
	delete last;
	delete[] data;
}

PGMImage* PGMImage::clone() const {
	return new PGMImage(*this);
}