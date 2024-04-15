#pragma once
#include "Image.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"
#include "Grayscale.hpp"
#include "Monochrome.hpp"
#include "Negative.hpp"
#include "Rotate.hpp"
#include "Collage.hpp"

class Session {
private:
	int id = 0;
	Image** imageFiles = new Image* [10];
	size_t numberOfImages = 0;
	size_t maxNumberOfImages = 10;
	char** commands = new char* [10];
	size_t numberOfCommands = 0;
	size_t maxNumberOfCommands = 10;


public:
	Session() = default;
	Session(const Session& other);
	Session& operator=(const Session& other);
	~Session();

	void setId(const int id);
	int getId() const;
	size_t getNumberOfImages() const { return numberOfImages; }
	Image** getImages() const { return imageFiles; }
	size_t getNumberOfCommands() const { return numberOfCommands; }
	char** getComands() const { return commands; }
	void setCommand(const char* command, const int i);
	void addImage(const char* fileName);
	void addCommand(const char* commandName);
	void removeLastCommand();
	void save(Image* image, const char* fileName = nullptr);
private:
	void copyFrom(const Session& other);
	void free();
	void resizeImages();
	void resizeCommands();
};