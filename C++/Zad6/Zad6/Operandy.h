#pragma once
#include "Wyrazenie.h"
#include <map>
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <vector>
#include <string>

class Liczba : public Wyrazenie
{
public:
	Liczba(int v);
	~Liczba();

	double val;

	std::string opis() override;
	double oblicz() override;
};

class Stala : public Wyrazenie
{
public:
	Stala();
	~Stala();
	
	virtual std::string opis() = 0;
	virtual double oblicz() = 0;
};

class Zmienna : public Wyrazenie
{
public:
	Zmienna(std::string nazwa);
	~Zmienna();

	std::string opis() override;
	double oblicz() override;
	static void zmien_wartosc(double v);
	static void dodaj(int poz, std::string nazwa, double v);
	int licznik = 0;

private:
	static std::vector<std::pair<std::string, double>> val;
};

class Pi : public Stala
{
public:
	Pi();
	~Pi();

	std::string opis() override;
	double oblicz() override;
};

class E : public Stala
{
public:
	E();
	~E();

	std::string opis() override;
	double oblicz() override;
};

class Fi : public Stala
{
public:
	Fi();
	~Fi();

	std::string opis() override;
	double oblicz() override;

};
