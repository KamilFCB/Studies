#pragma once
#include <iostream>
#include <string>

using namespace std;

class Kolejka
{
public:
	Kolejka::Kolejka();
	Kolejka(int rozmiar);
	Kolejka(initializer_list<string> k);
	Kolejka(const Kolejka &t);
	Kolejka(Kolejka &&t);
	Kolejka& Kolejka::operator = (const Kolejka &t);
	Kolejka& Kolejka::operator = (Kolejka &&t);
	~Kolejka();
	int rozmiar();
	void wstaw(string napis);
	string pobierz();
	string sprawdz();
	int pojemnosc_k();
	void wypisz();
	string* val;

private:
	int ile;
	int poczatek;
	int pojemnosc;
};

