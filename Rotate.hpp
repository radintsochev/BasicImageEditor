#pragma once
#include "Command.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"

template <typename T>
void rotateRightOneDimensionalMatrix(T* matrix, int rows, int cols) {
	T* rotated = new T[rows * cols];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			rotated[j * rows + (rows - 1 - i)] = matrix[i * cols + j];
		}
	}
	
	for (int i = 0; i < rows * cols; ++i) {
		matrix[i] = rotated[i];
	}
	delete[] rotated;
}

template <typename T>
void rotateLeftOneDimensionalMatrix(T* matrix, int rows, int cols) {
	T* rotated = new T[cols * rows];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			rotated[(cols - 1 - j) * rows + i] = matrix[i * cols + j];
		}
	}
	
	for (int i = 0; i < cols * rows; ++i) {
		matrix[i] = rotated[i];
	}
	delete[] rotated;
}

class RotatePPM : public Command<PPMImage> {
public:
	void apply(const char* direction, PPMImage& image) override{
		if (!strcmp(direction, "left"))
		{
			rotateLeftOneDimensionalMatrix<RGBPixel>(image.getData(), image.getHeight(), image.getWidth());
			int temp = image.getWidth();
			image.setWidth(image.getHeight());
			image.setHeight(temp);
		}
		else if (!strcmp(direction, "right"))
		{
			rotateRightOneDimensionalMatrix<RGBPixel>(image.getData(), image.getHeight(), image.getWidth());
			int temp = image.getWidth();
			image.setWidth(image.getHeight());
			image.setHeight(temp);
		}
		else
		{
			throw std::runtime_error("Invalid direction!");
		}
		
	}
};

class RotatePGM : public Command<PGMImage> {
public:
	void apply(const char* direction, PGMImage& image) override {
		if (!strcmp(direction, "left"))
		{
			rotateLeftOneDimensionalMatrix<int>(image.getData(), image.getHeight(), image.getWidth());
			int temp = image.getWidth();
			image.setWidth(image.getHeight());
			image.setHeight(temp);
		}
		else if (!strcmp(direction, "right"))
		{
			rotateRightOneDimensionalMatrix<int>(image.getData(), image.getHeight(), image.getWidth());
			int temp = image.getWidth();
			image.setWidth(image.getHeight());
			image.setHeight(temp);
		}
		else
		{
			throw std::runtime_error("Invalid direction!");
		}

	}
};

class RotatePBM : public Command<PBMImage> {
public:
	void apply(const char* direction, PBMImage& image) override {
		if (!strcmp(direction, "left"))
		{
			rotateLeftOneDimensionalMatrix<bool>(image.getData(), image.getHeight(), image.getWidth());
			int temp = image.getWidth();
			image.setWidth(image.getHeight());
			image.setHeight(temp);
		}
		else if (!strcmp(direction, "right"))
		{
			rotateRightOneDimensionalMatrix<bool>(image.getData(), image.getHeight(), image.getWidth());
			int temp = image.getWidth();
			image.setWidth(image.getHeight());
			image.setHeight(temp);
		}
		else
		{
			throw std::runtime_error("Invalid direction!");
		}

	}
};