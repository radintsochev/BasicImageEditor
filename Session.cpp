#pragma once
#include "Session.h"

int getFileType(std::ifstream& imageFileIn) {
	imageFileIn.seekg(1, std::ios::beg);
	int type = imageFileIn.get() - '0';
	imageFileIn.seekg(0, std::ios::beg);
	return type;
}

void Session::copyFrom(const Session& other) {
	setId(other.getId());
	numberOfImages = other.numberOfImages;
	maxNumberOfImages = other.maxNumberOfImages;
	imageFiles = new Image*[maxNumberOfImages];
	for (size_t i = 0; i < numberOfImages; i++)
	{
		imageFiles[i] = other.imageFiles[i];
	}

	numberOfCommands = other.numberOfCommands;
	maxNumberOfCommands = other.maxNumberOfCommands;
	commands = new char* [maxNumberOfCommands];
	for (size_t i = 0; i < numberOfCommands; i++)
	{
		strcpy(commands[i], other.commands[i]);
	}
}

void Session::free() {
	id = 0;
	numberOfImages = 0;
	maxNumberOfImages = 0;
	for (size_t i = 0; i < numberOfCommands; i++)
	{
		if (commands[i])
		{
			delete commands[i];
		}
	}
	delete[] commands;
	numberOfCommands = 0;
	maxNumberOfCommands = 0;
}

Session::Session(const Session& other) {
	copyFrom(other);
}

Session& Session::operator=(const Session& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Session::~Session() {
	free();
}

void Session::setId(const int id) {
	this->id = id;
}

int Session::getId() const {
	return id;
}

void Session::resizeImages() {
	 maxNumberOfImages += 10;
	 Image** temp = new Image*[maxNumberOfImages];
	 for (size_t i = 0; i < numberOfImages; i++)
	 {
		 temp[i] = imageFiles[i];
	 }
	 imageFiles = temp;
	 delete[] temp;
}

void Session::resizeCommands() {
	maxNumberOfCommands += 10;
	char** temp = new char*[maxNumberOfCommands];
	for (size_t i = 0; i < numberOfCommands; i++)
	{
		int length = strlen(commands[i]);
		temp[i] = new char[length + 1];
		for (size_t j = 0; j < length; j++)
		{
			temp[i][j] = commands[i][j];
		}
		commands[i][length] = '\0';
	}
	commands = temp;
	delete[] temp;
}


void Session::addImage(const char* fileName) {
	addCommand(fileName);
	std::ifstream imageFileIn(fileName, std::ios::binary | std::ios::in);
	if (!imageFileIn.is_open())
	{
		throw std::runtime_error("File did not open!");
	}

	int fileType = getFileType(imageFileIn);

	if (fileType == 3 || fileType == 6)
	{
		PPMImage* image = new PPMImage();
		image->load(imageFileIn);
		if (numberOfImages == maxNumberOfImages)
		{
			resizeImages();
		}
		image->setFileName(fileName);
		imageFiles[numberOfImages] = image;
		numberOfImages++;
	}
	else if (fileType == 2 || fileType == 5)
	{
		PGMImage* image = new PGMImage();
		image->load(imageFileIn);
		if (numberOfImages == maxNumberOfImages)
		{
			resizeImages();
		}
		image->setFileName(fileName);
		imageFiles[numberOfImages] = image;
		numberOfImages++;
	}
	else if (fileType == 1 || fileType == 4)
	{
		PBMImage* image = new PBMImage();
		image->load(imageFileIn);
		if (numberOfImages == maxNumberOfImages)
		{
			resizeImages();
		}
		image->setFileName(fileName);
		imageFiles[numberOfImages] = image;
		numberOfImages++;
	}
	else 
	{
		throw std::runtime_error("Invalid file format!");
	}

	imageFileIn.close();
}

void Session::save(Image* image, const char* fileName) {
	if (fileName != nullptr)
	{
		image->setFileName(fileName);
	}
	addCommand(image->getFileName());
	addCommand("save");
	PNMImage* pnmImage = (PNMImage*)image;
	int i = numberOfCommands - 3;
	while (i > 0)
	{
		if (strcmp(image->getFileName(), commands[i]) != 0)
		{
			--i;
		}
		else {
			break;
		}
		
	}
	for (size_t j = i; j < numberOfCommands; j++)
	{
		if (!strcmp(commands[j], "grayscale"))
		{
			if (pnmImage->getType() == 1 || pnmImage->getType() == 4)
			{
				PBMImage* pbmImage = (PBMImage*)pnmImage;
				GrayscalePBM command;
				command.apply(*pbmImage);
			}
			else if (pnmImage->getType() == 2 || pnmImage->getType() == 5)
			{
				PGMImage* pgmImage = (PGMImage*)pnmImage;
				GrayscalePGM command;
				command.apply(*pgmImage);
			}
			else if (pnmImage->getType() == 3 || pnmImage->getType() == 6)
			{
				PPMImage* ppmImage = (PPMImage*)pnmImage;
				ppmImage->setLast(ppmImage->clone());
				GrayscalePPM command;
				command.apply(*ppmImage);
			}
		}
		else if (!strcmp(commands[j], "monochrome"))
		{
			if (pnmImage->getType() == 1 || pnmImage->getType() == 4)
			{
				PBMImage* pbmImage = (PBMImage*)pnmImage;
				MonochromePBM command;
				command.apply(*pbmImage);
			}
			else if (pnmImage->getType() == 2 || pnmImage->getType() == 5)
			{
				PGMImage* pgmImage = (PGMImage*)pnmImage;
				pgmImage->setLast(pgmImage->clone());
				MonochromePGM command;
				command.apply(*pgmImage);
			}
			else if (pnmImage->getType() == 3 || pnmImage->getType() == 6)
			{
				PPMImage* ppmImage = (PPMImage*)pnmImage;
				ppmImage->setLast(ppmImage->clone());
				MonochromePPM command;
				command.apply(*ppmImage);
			}
		}
		else if (!strcmp(commands[j], "negative"))
		{
			if (pnmImage->getType() == 1 || pnmImage->getType() == 4)
			{
				PBMImage* pbmImage = (PBMImage*)pnmImage;
				NegativePBM command;
				command.apply(*pbmImage);
			}
			else if (pnmImage->getType() == 2 || pnmImage->getType() == 5)
			{
				PGMImage* pgmImage = (PGMImage*)pnmImage;
				NegativePGM command;
				command.apply(*pgmImage);
			}
			else if (pnmImage->getType() == 3 || pnmImage->getType() == 6)
			{
				PPMImage* ppmImage = (PPMImage*)pnmImage;
				NegativePPM command;
				command.apply(*ppmImage);
			}
		}
		else if (!strcmp(commands[j], "rotateleft"))
		{
			if (pnmImage->getType() == 1 || pnmImage->getType() == 4)
			{
				PBMImage* pbmImage = (PBMImage*)pnmImage;
				RotatePBM command;
				command.apply("left", * pbmImage);
			}
			else if (pnmImage->getType() == 2 || pnmImage->getType() == 5)
			{
				PGMImage* pgmImage = (PGMImage*)pnmImage;
				RotatePGM command;
				command.apply("left", *pgmImage);
			}
			else if (pnmImage->getType() == 3 || pnmImage->getType() == 6)
			{
				PPMImage* ppmImage = (PPMImage*)pnmImage;
				RotatePPM command;
				command.apply("left", *ppmImage);
			}
		}
		else if (!strcmp(commands[j], "rotateright"))
		{
			if (pnmImage->getType() == 1 || pnmImage->getType() == 4)
			{
				PBMImage* pbmImage = (PBMImage*)pnmImage;
				RotatePBM command;
				command.apply("right", * pbmImage);
			}
			else if (pnmImage->getType() == 2 || pnmImage->getType() == 5)
			{
				PGMImage* pgmImage = (PGMImage*)pnmImage;
				RotatePGM command;
				command.apply("right", *pgmImage);
			}
			else if (pnmImage->getType() == 3 || pnmImage->getType() == 6)
			{
				PPMImage* ppmImage = (PPMImage*)pnmImage;
				RotatePPM command;
				command.apply("right", *ppmImage);
			}
		}
	}
	std::ofstream imageFileOut(image->getFileName(), std::ios::binary | std::ios::out);
	if (!imageFileOut.is_open())
	{
		throw std::runtime_error("File did not open!");
	}
	image->save(imageFileOut);
}

void Session::addCommand(const char* commandName) {
	if (numberOfCommands == maxNumberOfCommands)
	{
		resizeCommands();
	}
	commands[numberOfCommands] = new char[strlen(commandName) + 1];
	strcpy(commands[numberOfCommands], commandName);
	numberOfCommands++;
}

void Session::removeLastCommand() {
	if (numberOfCommands)
	{
		--numberOfCommands;
	}
}

void Session::setCommand(const char* command, const int i) {
	int lenght = strlen(command);
	commands[i] = new char[lenght + 1];
	strcpy(commands[i], command);
}