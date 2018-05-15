#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

class PlikWejsciowy
{
public:
	PlikWejsciowy(std::string name);
	~PlikWejsciowy();
	void printLine();

private:
	std::fstream file;
};