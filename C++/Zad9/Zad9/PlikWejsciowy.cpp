#include "stdafx.h"
#include "PlikWejsciowy.h"


PlikWejsciowy::PlikWejsciowy(std::string name)
{
	file.open(name, std::ios::in);
	if (file.good() != true)
		// throw
		std::cout << "ERR" << std::endl;
}


PlikWejsciowy::~PlikWejsciowy()
{
	file.close();
}

void PlikWejsciowy::printLine()
{
	std::string line;

	if(!file.eof())
		getline(file, line);

	if(line[line.length() - 1] == '\n')
		line[line.length() - 1] = '\0';

	std::cout << line;
}
