#pragma once

using namespace std;
#include<string>

class Wyrazenie
{
public:
	Wyrazenie();
	~Wyrazenie();

	virtual string opis() = 0;
	virtual double oblicz() = 0;

};

