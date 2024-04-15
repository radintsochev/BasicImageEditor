#include "Program.h"

void Program::copyFrom(const Program& other) {
	numberOfSessions = other.numberOfSessions;
	maxNumberOfSessions = other.maxNumberOfSessions;
	sessions = new Session[other.maxNumberOfSessions];
	for (size_t i = 0; i < numberOfSessions; i++)
	{
		sessions[i] = other.sessions[i];
	}
	current = other.current;
	numberOfClosed = other.numberOfClosed;
	maxNumberOfClosed = other.maxNumberOfClosed;
	closedSessions = new int[maxNumberOfClosed];
	for (size_t i = 0; i < numberOfClosed; i++)
	{
		closedSessions[i] = other.closedSessions[i];
	}
}

void Program::free() {
	delete[] sessions;
	delete[] closedSessions;
}

void Program::resize() {
	maxNumberOfSessions += 10;
	Session* temp = new Session[maxNumberOfSessions];
	for (size_t i = 0; i < numberOfSessions; i++)
	{
		temp[i] = sessions[i];
	}
	sessions = temp;
	delete[] temp;
}

void Program::resizeClosed() {
	maxNumberOfClosed += 10;
	int* temp = new int[maxNumberOfClosed];
	for (size_t i = 0; i < numberOfClosed; i++)
	{
		temp[i] = closedSessions[i];
	}
	closedSessions = temp;
	delete[] temp;
}


Program::Program(const Program& other) {
	copyFrom(other);
}

Program& Program::operator=(const Program& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Program::~Program() {
	free();
}

void Program::load(const char** fileNames, const int numberOfFiles) {
	if (numberOfSessions == maxNumberOfSessions)
	{
		resize();
	}
	Session newSession;
	sessions[numberOfSessions] = newSession;
	current = numberOfSessions;
	++numberOfSessions;
	std::cout << "Session with ID " << current << " started" << std::endl;
	for (size_t i = 0; i < numberOfFiles; i++)
	{
		add(fileNames[i]);
	}
}

void Program::add(const char* fileName) {
	sessions[current].addImage(fileName);
	std::cout << "Image " << fileName << " added" << std::endl;
}

void Program::save() {
	for (size_t i = 0; i < sessions[current].getNumberOfImages(); i++)
	{
		sessions[current].save(sessions[current].getImages()[i]);
	}
}

void Program::saveAs(const char** fileNames, const int numberOfFiles) {
	for (size_t i = 0; i < numberOfFiles; i++)
	{
		sessions[current].save(sessions[current].getImages()[i], fileNames[i]);
	}
}

void Program::close() {
	if (numberOfClosed == maxNumberOfClosed)
	{
		resizeClosed();
	}
	closedSessions[numberOfClosed] = current;
	for (size_t i = 0; i < numberOfSessions; i++)
	{
		if (isOpen(i))
		{
			current = i;
			break;
		}
	}
}

void Program::undo() {
	bool saved = false;
	int lastCommand = sessions[current].getNumberOfCommands() - 1;
	while (!strcmp(sessions[current].getComands()[lastCommand], "save") || !strcmp(sessions[current].getComands()[lastCommand], "undo"))
	{
		if (!strcmp(sessions[current].getComands()[lastCommand], "save"))
		{
			saved = true;
		}
		lastCommand -= 2;
	}
	bool entered = false;
	while (!entered && lastCommand >= 0)
	{
		if (!strcmp(sessions[current].getComands()[lastCommand], "rotateleft"))
		{
			sessions[current].setCommand("deleted", lastCommand);
			if (saved)
			{
				sessions[current].addCommand("rotateright");
				sessions[current].addCommand("undo");
			}
			entered = true;
		}
		else if (!strcmp(sessions[current].getComands()[lastCommand], "rotateright"))
		{
			sessions[current].setCommand("deleted", lastCommand);
			if (saved)
			{
				sessions[current].addCommand("rotateleft");
				sessions[current].addCommand("undo");
			}	
			entered = true;
		}
		else if (!strcmp(sessions[current].getComands()[lastCommand], "negative"))
		{
			sessions[current].setCommand("deleted", lastCommand);
			if (saved)
			{
				sessions[current].addCommand("negative");
				sessions[current].addCommand("undo");
			}
			entered = true;
		}
		else if (!strcmp(sessions[current].getComands()[lastCommand], "grayscale") || !strcmp(sessions[current].getComands()[lastCommand], "monochrome"))
		{
			entered = true;
			if (saved)
			{
				for (size_t i = 0; i < sessions[current].getNumberOfImages(); i++)
				{
					PNMImage* pnmImage = (PNMImage*)sessions[current].getImages()[i];
					if (pnmImage->getType() == 2 || pnmImage->getType() == 5)
					{
						PGMImage* pgmImage = (PGMImage*)pnmImage;
						if (pgmImage->getLast())
						{
							sessions[current].getImages()[i] = pgmImage->getLast();
						}
					}
					else if (pnmImage->getType() == 3 || pnmImage->getType() == 6)
					{
						PPMImage* ppmImage = (PPMImage*)pnmImage;
						if (ppmImage->getLast())
						{
							sessions[current].getImages()[i] = ppmImage->getLast();
						}
					}
				}
			}
			
		}
		--lastCommand;
	}
}

void Program::switchTo(const int id) {
	bool found = false;
	for (size_t i = 0; i < numberOfSessions; i++)
	{
		if (id == i)
		{
			current = id;
			found = true;
		}
	}
	if (!found)
	{
		throw std::runtime_error("Could not find a session with such ID.");
	}
}

bool Program::isClosed(const int id) {
	for (size_t i = 0; i < numberOfClosed; i++)
	{
		if (id == closedSessions[i])
		{
			return true;
		}
	}
	return false;
}

bool Program::isOpen(const int id) {
	for (size_t i = 0; i < numberOfSessions; i++)
	{
		if (!isClosed(id) && id == sessions[i].getId())
		{
			return true;
		}
	}
	return false;
}

void Program::info() {
	std::cout << "Name of images in the session: ";
        for (size_t i = 0; i < sessions[current].getNumberOfImages(); i++)
        {
            std::cout << sessions[current].getImages()[i]->getFileName() << " ";
        }
        std::cout << std::endl;
        std::cout << "Pending transformations: ";
        int j = sessions[current].getNumberOfCommands() - 1;
        while (!strcmp(sessions[current].getComands()[j], "save") || j != 0) {
            --j;
        }
        for (size_t i = j; i < sessions[current].getNumberOfCommands(); i++)
        {
            if (!strcmp(sessions[current].getComands()[i], "grayscale"))
            {
                std::cout << "grayscale, ";
            }
            else if (!strcmp(sessions[current].getComands()[i], "monochrome"))
            {
                std::cout << "monochrome, ";
            }
            else if (!strcmp(sessions[current].getComands()[i], "negative"))
            {
                std::cout << "negative, ";
                if (i != sessions[current].getNumberOfCommands() - 1 && !strcmp(sessions[current].getComands()[i + 1], "negative"))
                {
                    ++i;
                }
            }
            else if (!strcmp(sessions[current].getComands()[i], "rotateleft"))
            {
                std::cout << "rotate left, ";
                if (i != sessions[current].getNumberOfCommands() - 1 && !strcmp(sessions[current].getComands()[i + 1], "rotateright"))
                {
                    ++i;
                }
            }
            else if (!strcmp(sessions[current].getComands()[i], "rotateright"))
            {
                std::cout << "rotate right, ";
                if (i != sessions[current].getNumberOfCommands() - 1 && !strcmp(sessions[current].getComands()[i + 1], "rotateleft"))
                {
                    ++i;
                }
            }
        }
        std::cout << std::endl;
}

void Program::help() const {
	std::cout << "All commands should start with '> '." << std::endl;
	std::cout << "load <image file> ... <image file> - Starts a new session and adds the" << std::endl;
	std::cout << "images to that session." << std::endl;
	std::cout << "add <image> - adds an image to the current session." << std::endl;
	std::cout << "switch <sessionID> - switches to another open session." << std::endl;
	std::cout << "grayscale - applies grayscale to all images in the current session." << std::endl;
	std::cout << "monochrome - applies monochrome to all images in the current session." << std::endl;
	std::cout << "negative - applies negative to all images in the current session." << std::endl;
	std::cout << "rotate <direction> - valid directions are [left, right], rotates all" << std::endl;
	std::cout << "images in the current session 90 degrees in that direction." << std::endl;
	std::cout << "collage <direction> <image1> <image2> <outimage> - valid directions are" << std::endl;
	std::cout << "[horizontal, vertical], makes a collage using two images from the current" << std::endl;
	std::cout << "session and saves it in a new image that is added to the current session." << std::endl;
	std::cout << "undo - undos the last transformation." << std::endl;
	std::cout << "session info - prints information about the current session" << std::endl;
	std::cout << "save - saves all images in the current session." << std::endl;
	std::cout << "save as <file name> ... <file name> - save all images in the current" << std::endl;
	std::cout << "session with the provided names(the number of names should be equal" << std::endl;
	std::cout << "to the number of images in the session)." << std::endl;
	std::cout << "close - closes the current session." << std::endl;
	std::cout << "exit - closes all sessions and exits the program." << std::endl;
	std::cout << "about - prints information about the developer." << std::endl;
}