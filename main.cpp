#include <iostream>
#include <sstream>
#include "PBMImage.h"
#include "PGMImage.h"
#include "PPMImage.h"
#include "Session.h"
#include "Program.h"

int charToInt(const char* str) {
    std::stringstream ss(str);
    int result;
    ss >> result;
    return result;
}

void processCommand(Program& program, const char* command) {
    std::istringstream iss(command);
    char** words = nullptr;
    int numWords = 0;

    while (iss) {
        char* word = new char[256];
        iss >> word;
        if (word[0] != '\0') {
            char** temp = new char* [numWords + 1];
            for (int i = 0; i < numWords; ++i) {
                temp[i] = words[i];
            }
            temp[numWords] = word;
            delete[] words;
            words = temp;

            ++numWords;
        }
        else {
            delete[] word;
        }
    }

    if (!strcmp(words[0], "load"))
    {
        if (numWords != 1)
        {
            program.load((const char**)words + 1, numWords - 1);
        }
        else
        {
            std::cout << "Command \"load\" needs atleast one argument." << std::endl;
        }
    }
    else if (!strcmp(words[0], "save") && numWords == 1)
    {
        program.save();
    }
    else if ((!strcmp(words[0], "save") && !strcmp(words[1], "as")))
    {
        if (program.getSessions()[program.getCurrent()].getNumberOfImages() == numWords - 2)
        {
            program.saveAs((const char**)words + 2, numWords - 2);
        }
        else
        {
            std::cout << "Command \"save as\" must have as much arguments as images in the current session." << std::endl;
        }
    }
    else if (!strcmp(words[0], "grayscale"))
    {
        program.getSessions()[program.getCurrent()].addCommand("grayscale");
    }
    else if (!strcmp(words[0], "monochrome"))
    {
        program.getSessions()[program.getCurrent()].addCommand("monochrome");
    }
    else if (!strcmp(words[0], "negative"))
    {
        program.getSessions()[program.getCurrent()].addCommand("negative");
    }
    else if (!strcmp(words[0], "rotate") && !strcmp(words[1], "left"))
    {
        program.getSessions()[program.getCurrent()].addCommand("rotateleft");
    }
    else if (!strcmp(words[0], "rotate") && !strcmp(words[1], "right"))
    {
        program.getSessions()[program.getCurrent()].addCommand("rotateright");
    }
    else if (!strcmp(words[0], "undo"))
    {
        program.undo();
    }
    else if (!strcmp(words[0], "add")) {
        if (numWords == 2)
        {
            program.getSessions()[program.getCurrent()].addImage(words[1]);
        }
        else
        {
            std::cout << "Command \"add\" must have only one argument.";
        }
    }
    else if (!strcmp(words[0], "session") && !strcmp(words[1], "info")) 
    {
        program.info();
    }
    else if (!strcmp(words[0], "switch"))
    {
        int id = charToInt(words[1]);
        if (program.isOpen(id))
        {
            program.switchTo(id);
            std::cout << "You switched to session with ID :" << words[1] << std::endl;
            program.info();
        }
        else
        {
            std::cout << "There is no session with that ID." << std::endl;
        }
        
    }
    else if (!strcmp(words[0], "collage"))
    {   
        int i1 = -1;
        int i2 = -1;
        for (size_t i = 0; i < program.getSessions()[program.getCurrent()].getNumberOfImages(); i++)
        {
            if (!strcmp(words[2], program.getSessions()[program.getCurrent()].getImages()[i]->getFileName()))
            {
                i1 = i;
            }
            if (!strcmp(words[3], program.getSessions()[program.getCurrent()].getImages()[i]->getFileName()))
            {
                i2 = i;
            }
        }
        if (i1 == -1)
        {
            std::cout << "Could not find image withe name " << words[2] << " in current session." << std::endl;
        }
        else if (i2 == -1)
        {
            std::cout << "Could not find image withe name " << words[3] << " in current session." << std::endl;
        }
        else 
        {
            PNMImage* image1 = (PNMImage*)program.getSessions()[program.getCurrent()].getImages()[i1];
            PNMImage* image2 = (PNMImage*)program.getSessions()[program.getCurrent()].getImages()[i2];
            if (image1->getType() == 1 || image1->getType() == 4)
            {
                PBMImage* pbmImage1 = (PBMImage*)image1;
                PBMImage* pbmImage2 = (PBMImage*)image2;
                CollagePBM collage;
                collage.apply(words[1], *pbmImage1, *pbmImage2, words[4]);
                program.add(words[4]);
            }
            else if (image1->getType() == 2 || image1->getType() == 5)
            {
                PGMImage* pgmImage1 = (PGMImage*)image1;
                PGMImage* pgmImage2 = (PGMImage*)image2;
                CollagePGM collage;
                collage.apply(words[1], *pgmImage1, *pgmImage2, words[4]);
                program.add(words[4]);
            }
            else if (image1->getType() == 3 || image1->getType() == 6)
            {
                PPMImage* ppmImage1 = (PPMImage*)image1;
                PPMImage* ppmImage2 = (PPMImage*)image2;
                CollagePPM collage;
                collage.apply(words[1], *ppmImage1, *ppmImage2, words[4]);
                program.add(words[4]);
            }
        }
    }
    else if (!strcmp(words[0], "close"))
    {
        if (strcmp(program.getSessions()[program.getCurrent()].getComands()[program.getSessions()[program.getCurrent()].getNumberOfCommands() - 1], "save"))
        {
            while (true)
            {
                std::cout << "You have unsaved changes. Do you want to save them? (y/n)" << std::endl;
                char* answer = new char[2];
                std::cin.getline(answer, 2);
                program.close();
                if (!strcmp(answer, "y"))
                {
                    program.save();
                    break;
                }
                else if (!strcmp(answer, "n"))
                {
                    break;
                }
            }

        }
    }
    else if (!strcmp(words[0], "exit"))
    {
        if (strcmp(program.getSessions()[program.getCurrent()].getComands()[program.getSessions()[program.getCurrent()].getNumberOfCommands() - 1], "save")) 
        {
            while (true)
            {
                std::cout << "You have unsaved changes. Do you want to save them? (y/n)" << std::endl;
                char* answer = new char[2];
                std::cin.getline(answer, 2);
                if (!strcmp(answer, "y"))
                {
                    for (size_t i = 0; i < program.getNumberOfSessions(); i++)
                    {
                        if (program.isOpen(i))
                        {
                            program.switchTo(i);
                            program.save();
                        }
                    }
                }
                else if (!strcmp(answer, "n"))
                {
                    break;
                }
            }
        }
    }
    else if (!strcmp(words[0], "help"))
    {
        program.help();
    }
    else if (!strcmp(words[0], "about"))
    {
        std::cout << "This program was writen in C++ by Radin Tsochev https://github.com/radintsochev" << std::endl;
    }

    for (int i = 0; i < numWords; ++i) {
        delete[] words[i];
    }
    delete[] words;
}

void menu() {
    Program program;
    const int initialBufferSize = 64;
    char* userInput = new char[initialBufferSize];
    int bufferSize = initialBufferSize;

    std::cout << "Use \"help\" for information about the commands." << std::endl;

    while (true) {
        std::cout << "> ";
        std::cin.getline(userInput, bufferSize);

        try
        {
            processCommand(program, userInput);
        }
        catch (const std::runtime_error e)
        {
            std::cout << e.what() << std::endl;
        }

        if (std::strcmp(userInput, "> exit") == 0) {
            std::cout << "Exiting program..." << std::endl;
            delete[] userInput;
            break;
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (std::cin.gcount() == bufferSize - 1) {
            char* largerBuffer = new char[bufferSize * 2];
            std::strcpy(largerBuffer, userInput);
            delete[] userInput;
            userInput = largerBuffer;
            bufferSize *= 2;
        }
    }
}

int main()
{
     menu();
}