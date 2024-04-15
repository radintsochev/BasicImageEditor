#include "PBMImage.h"

PBMImage::PBMImage(const PBMImage& other) : PNMImage(other) {
	setData(other.data);
}

PBMImage& PBMImage::operator=(const PBMImage& other) {
	if (this != &other)
	{
		PNMImage::operator=(other);
		setData(other.data);
	}
	return *this;
}

void PBMImage::setData(const bool* data) {
	this->data = new bool[dataLength];
	for (size_t i = 0; i < dataLength; i++)
	{
		this->data[i] = data[i];
	}
}

char* PBMImage::load(std::ifstream& imageFile) {
	char* fileData = PNMImage::load(imageFile);

	//Set the image data:
	bool* data = new bool[this->dataLength];
	int i = 0;
	while (i != dataLength)
	{
		while (fileData[i] == '\0')
		{
			i++;
		}
		data[i] = (bool)((unsigned char)fileData[i]);
		i++;
	}
	setData(data);

	delete[] fileData;
	return nullptr;
}

void PBMImage::save(std::ofstream& imageFile) const {
	PNMImage::save(imageFile);

	for (size_t i = 0; i < dataLength; i++)
	{
		imageFile.put((char)data[i]);
	}

	imageFile.close();
}

PBMImage::~PBMImage() {
	free();
}

void PBMImage::free() {
	delete[] data;
}