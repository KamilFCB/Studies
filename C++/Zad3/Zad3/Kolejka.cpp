#include "stdafx.h"
#include "Kolejka.h"


Kolejka::Kolejka() : Kolejka(4) // konstruktor delegatowy
{
}

Kolejka::Kolejka(int rozmiar)
{
	val = new string[rozmiar];
	ile = 0;
	poczatek = 0;
	pojemnosc = rozmiar;
}

Kolejka::Kolejka(initializer_list<string> k)
{
	val = new string[k.size()];
	int i = 0;
	for (auto it = k.begin(); it != k.end(); ++it)
	{
		val[i] = *it;
		i++;
	}
	ile = i;
	poczatek = 0;
	pojemnosc = i;
}

Kolejka::Kolejka(const Kolejka &t)
{
	val = new string[t.pojemnosc];
	for (int i = 0; i < t.pojemnosc; i++)
	{
		val[i] = t.val[i];
	}
	ile = t.ile;
	poczatek = t.poczatek;
	pojemnosc = t.pojemnosc;
}

Kolejka::Kolejka(Kolejka &&t)
{
	val = t.val;
	t.val = nullptr;
	pojemnosc = t.pojemnosc;
	ile = t.ile;
	poczatek = t.poczatek;
}

Kolejka& Kolejka::operator = (const Kolejka &t)
{
	if (this == &t) return *this;
	for (int i = 0; i < pojemnosc && i < t.pojemnosc; i++)
		val[i] = t.val[i];
	for (int i = t.pojemnosc; i < pojemnosc; i++)
		val[i] = "";
	return *this;
}

Kolejka& Kolejka::operator = (Kolejka &&t)
{
	if (this == &t) return *this;
	for (int i = 0; i < pojemnosc && i < t.pojemnosc; i++)
		val[i] = t.val[i];
	for (int i = t.pojemnosc; i < pojemnosc; i++)
		val[i] = "";
	return *this;
}

Kolejka::~Kolejka()
{
	delete[] val;
}

int Kolejka::rozmiar()
{
	return ile - poczatek;
}

void Kolejka::wstaw(string napis)
{
	if (ile == pojemnosc)
		throw string("Kolejka jest pelna");
	val[ile] = napis;
	ile++;
	
}

string Kolejka::pobierz()
{
	poczatek++;
	return val[poczatek-1];
}

string Kolejka::sprawdz()
{
	if (val[poczatek] != "")
		return val[poczatek];
	return "Kolejka pusta";
}

int Kolejka::pojemnosc_k()
{
	return pojemnosc;
}

void Kolejka::wypisz()
{
	if (ile == poczatek)
		cout << val[poczatek] << endl;
	else
	{
		for (int i = poczatek; i < ile - poczatek; i++)
			cout << val[i] << endl;
	}
}
