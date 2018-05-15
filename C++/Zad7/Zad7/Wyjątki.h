#pragma once
#include <iostream>

class wyjatek_wymierny 
{
public:
	virtual void wypisz() = 0;
};

class dzielenie_przez_0 : public wyjatek_wymierny
{
public:
	void wypisz();
private:
	std::string str = "dzielenie przez 0";
};

class przekroczenie_zakresu : public wyjatek_wymierny
{
public:
	void wypisz();
private:
	std::string str = "przekroczenie zakresu int";
};

class mianownik_rowny_0 : public wyjatek_wymierny
{
public:
	void wypisz();
private:
	std::string str = "mianownik rowny 0";
};

class licznik_rowny_0 : public wyjatek_wymierny
{
public:
	void wypisz();
private:
	std::string str = "licznik rowny 0";
};




