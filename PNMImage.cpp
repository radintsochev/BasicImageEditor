#include "PNMImage.h"

int numberOfDigits(int number) {
	int counter = 0;
	while (number != 0)
	{
		number /= 10;
		counter++;
	}
	return counter;
}

char* PNMImage::load(std::ifstream& imageFile) {
	imageFile.seekg(0, std::ios::beg);
	size_t fileBeg = imageFile.tellg();
	imageFile.seekg(0, std::ios::end);
	size_t fileEnd = imageFile.tellg();
	int fileLength = fileEnd - fileBeg;
	imageFile.seekg(0, std::ios::beg);

	char* fileData = new char[fileLength + 1];
	char currentChar;
	int i = 0;

	while (imageFile.get(currentChar))
	{
		fileData[i] = currentChar;
		i++;
	}
	fileData[i] = '\0';

	imageFile.close();

	//Read the file type:
	i = 1;

	setType(fileData[i] - '0');

	i += 2;

	//Skip any comments(assuming comments are located only between the file type and the width and height):
	while (fileData[i] == '#')
	{
		while (fileData[i] != '\n')
		{
			i++;
		}
		i++;
	}
	

	//Read the image width and height:
	int width = 0;
	while (fileData[i] != ' ')
	{
		width *= 10;
		width += (fileData[i] - '0');
		i++;
	}
	setWidth(width);
	i++;

	int height = 0;
	while (fileData[i] != '\n')
	{
		height *= 10;
		height += (fileData[i] - '0');
		i++;
	}
	setHeight(height);
	i++;

	//Read the pixel max value:
	int maxValue = 0;
	while (fileData[i] != '\n')
	{
		maxValue *= 10;
		maxValue += (fileData[i] - '0');
		i++;
	}
	setMaxValue(maxValue);
	i++;

	//Set the data length:
	setDataLength(fileLength - i);


	char* newFileData = new char[dataLength + 1];
	for (size_t k = 0; k < dataLength; k++)
	{
		newFileData[k] = fileData[k + i];
	}
	newFileData[i] = '\0';

	delete[] fileData;

	return newFileData;
}

void PNMImage::save(std::ofstream& imageFile) const {

	imageFile.put('P');
	if (type == 4)
	{
		imageFile.put('4');
	}
	else if (type == 5)
	{
		imageFile.put('5');
	}
	else if (type == 6)
	{
		imageFile.put('6');
	}
	imageFile.put('\n');

	int width = this->width;
	int digitsOfWidth = numberOfDigits(width);
	while (width >= 0)
	{
		if (width == 0)
		{
			for (size_t i = 0; i < digitsOfWidth; i++)
			{
				imageFile.put('0');
			}
			
			break;
		}
		char digit = width / pow(10, digitsOfWidth - 1);
		digit += '0';
		imageFile.put(digit);
		width %= (int)(pow(10, digitsOfWidth - 1));
		digitsOfWidth--;
	}

	imageFile.put(' ');
	
	int height = this->height;
	int digitsOfHeight = numberOfDigits(height);
	while (height >= 0)
	{
		if (height == 0)
		{
			for (size_t i = 0; i < digitsOfHeight; i++)
			{
				imageFile.put('0');
			}

			break;
		}
		char digit = height / pow(10, digitsOfHeight - 1);
		digit += '0';
		imageFile.put(digit);
		height %= (int)(pow(10, digitsOfHeight - 1));
		digitsOfHeight--;
	}

	imageFile.put('\n');

	int maxValue = this->maxValue;
	int digitsOfMaxValue = numberOfDigits(maxValue);
	while (maxValue > 0)
	{
		if (maxValue == 0)
		{
			for (size_t i = 0; i < digitsOfMaxValue; i++)
			{
				imageFile.put('0');
			}

			break;
		}
		char digit = maxValue / pow(10, digitsOfMaxValue - 1);
		digit += '0';
		imageFile.put(digit);
		maxValue %= (int)(pow(10, digitsOfMaxValue - 1));
		digitsOfMaxValue--;
	}

	imageFile.put('\n');
}


void PNMImage::setType(const int type) {
	if (type >= 1 && type <= 6)
	{
		this->type = type;
	}
	else
	{
		throw std::invalid_argument("Invalid type of file.");
	}
}

void PNMImage::setWidth(const int width) {
	if (width >= 0)
	{
		this->width = width;
	}
	else
	{
		throw std::invalid_argument("Invalid width.");
	}
}

void PNMImage::setHeight(const int height) {
	if (height >= 0)
	{
		this->height = height;
	}
	else
	{
		throw std::invalid_argument("Invalid height.");
	}
}

void PNMImage::setMaxValue(const int maxValue) {
	if (maxValue >= 0)
	{
		this->maxValue = maxValue;
	}
	else
	{
		throw std::invalid_argument("Invalid maxValue.");
	}
}

void PNMImage::setDataLength(const int dataLength) {
	if (dataLength >= 0)
	{
		this->dataLength = dataLength;
	}
	else
	{
		throw std::invalid_argument("Invalid dataLength.");
	}
}

int PNMImage::getType() const{
	return type;
}

int PNMImage::getWidth() const{
	return width;
}

int PNMImage::getHeight() const{
	return height;
}

int PNMImage::getMaxValue() const{
	return maxValue;
}

int PNMImage::getDataLength() const{
	return dataLength;
}