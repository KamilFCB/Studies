#pragma once
#include <iostream>

using namespace std;

class Lista
{
public:
	Lista();
	Lista(int v);
	~Lista();
	void wypisz();

public:
	class Wezel
	{
	public:
		Wezel();
		Wezel(double v);
		~Wezel();

		Wezel *prev;
		Wezel *next;
		double val;

		void dodaj(double v, int poz);

	};
public:
	 Wezel *pierwszy;
	 Wezel *ostatni;

};