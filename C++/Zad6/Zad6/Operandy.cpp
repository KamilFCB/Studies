#include "stdafx.h"
#include "Operandy.h"
#include <string>

Stala::Stala()
{}

Stala::~Stala()
{}

Zmienna::Zmienna(std::string nazwa)
{
	val.emplace_back(nazwa, 0);
}

Zmienna::~Zmienna()
{}

Pi::Pi()
{}

E::E()
{}

Fi::Fi()
{}

Pi::~Pi()
{}

E::~E()
{}

Fi::~Fi()
{}

Liczba::Liczba(int v)
{
	val = v;
}

Liczba::~Liczba()
{}

double Liczba::oblicz()
{
	return val;
}

std::string Liczba::opis()
{
	return std::to_string(val);
}

double Zmienna::oblicz()
{
	return val[licznik].second;
}

std::string Zmienna::opis()
{
	return this->val[licznik].first.c_str();
	licznik++;
}

void Zmienna::zmien_wartosc(double v)
{
	for (int i = 0; i < val.size(); i++)
	{
		val[i].second = v;
	}
}

void Zmienna::dodaj(int poz, std::string nazwa, double v)
{
	if (val.size() <= poz)
	{
		/*val.back().first = nazwa;
		val.back().second = v;*/
		val.push_back(std::make_pair(nazwa, v));
		
	}
	else
	{
		val[poz].first = nazwa;
		val[poz].second = v;
	}
}

double Pi::oblicz()
{
	return M_PI;
}

std::string Pi::opis()
{
	return "pi";
}

double E::oblicz()
{
	return M_E;
}

std::string E::opis()
{
	return "e";
}

double Fi::oblicz()
{
	return 1.61803;
}

std::string Fi::opis()
{
	return "fi";
}