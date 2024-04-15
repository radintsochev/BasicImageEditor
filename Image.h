#pragma once
#pragma warning(disable: 4996)
#include <fstream>

class Image {
private:
    char* fileName = nullptr;
public:
    void setFileName(const char* fileName) {
        int length = strlen(fileName);
        this->fileName = new char[length + 1];
        strcpy(this->fileName, fileName);
        this->fileName[length] = '\0';
    }
    char* getFileName() const {
        return this->fileName;
    }
    virtual char* load(std::ifstream& imageFile) = 0;
    virtual void save(std::ofstream& imageFile) const = 0;
    virtual ~Image() {}
};