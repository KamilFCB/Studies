#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

class PlikWyjsciowy
{
public:
	PlikWyjsciowy();
	~PlikWyjsciowy();


private:
	std::fstream plik;
};

