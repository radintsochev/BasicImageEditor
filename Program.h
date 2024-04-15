#pragma once
#include "Session.h"
#include <iostream>

class Program {
private:
	Session* sessions = new Session[10];
	int numberOfSessions = 0;
	int maxNumberOfSessions = 10;
	int current = 0;
	int* closedSessions = new int[10];
	size_t numberOfClosed = 0;
	size_t maxNumberOfClosed = 10;
public:
	Program() = default;
	Program(const Program& other);
	Program& operator=(const Program& other);
	~Program();

	size_t getNumberOfSessions() { return numberOfSessions; }
	Session* getSessions() const { return sessions; }
	int getCurrent() const { return current; }
	bool isClosed(const int id);
	bool isOpen(const int id);

	void load(const char** fileNames, const int numberOfFiles);
	void add(const char* fileName);
	void save();
	void saveAs(const char** fileNames, const int numberOfFiles);
	void close();
	void info();
	void switchTo(const int id);
	void undo();
	void help() const;
private:
	void copyFrom(const Program& other);
	void free();
	void resize();
	void resizeClosed();
};