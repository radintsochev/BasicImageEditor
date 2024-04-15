#include "PPMImage.h"

PPMImage::PPMImage(const PPMImage& other) : PNMImage(other) {
	setData(other.data);
}

PPMImage& PPMImage::operator=(const PPMImage& other) {
	if (this != &other)
	{
		PNMImage::operator=(other);
		last = other.last;
		setData(other.data);
	}
	return *this;
}

void PPMImage::setData(const RGBPixel* data) {
	this->data = new RGBPixel[dataLength];
	for (size_t i = 0; i < dataLength / 3; i++)
	{
		this->data[i] = data[i];
	}
}

char* PPMImage::load(std::ifstream& imageFile) {
	char* fileData = PNMImage::load(imageFile);

	//Set the image data:
	RGBPixel* data = new RGBPixel[this->dataLength / 3];
	int i = 0;
	int j = 0;
	while (i != dataLength / 3)
	{
		
		data[i].red = (int)((unsigned char)fileData[j]);
		j++;

		
		data[i].green = (int)((unsigned char)fileData[j]);
		j++;

		
		data[i].blue = (int)((unsigned char)fileData[j]);
		j++;

		i++;
	}
	setData(data);

	delete[] fileData;
	return nullptr;
}

void PPMImage::save(std::ofstream& imageFile) const {
	PNMImage::save(imageFile);

	for (size_t i = 0; i < dataLength; i++)
	{
		imageFile.put((char)data[i].red);
		imageFile.put((char)data[i].green);
		imageFile.put((char)data[i].blue);
	}

	imageFile.close();
}

PPMImage::~PPMImage() {
	free();
}

void PPMImage::free() {
	delete last;
	delete[] data;
}

PPMImage* PPMImage::clone() const {
	return new PPMImage(*this);
}