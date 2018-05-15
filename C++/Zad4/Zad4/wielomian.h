#pragma once
#include<iostream>
#include <algorithm>

using namespace std;

class Wielomian
{
public:
	//konstruktory
	Wielomian();
	Wielomian(int st = 0, double wsp = 1);
	Wielomian(int st, const double wsp[]);
	Wielomian(initializer_list<double> wsp);
	Wielomian(const Wielomian &w);
	Wielomian(Wielomian &&w);
	Wielomian& operator = (const Wielomian &w);
	Wielomian& operator = (Wielomian &&w);
	~Wielomian();

	friend istream& operator >> (istream &we, Wielomian &w);
	friend ostream& operator << (ostream &wy, const Wielomian &w);
	friend Wielomian operator + (const Wielomian &u, const Wielomian &v);
	friend Wielomian operator - (const Wielomian &u, const Wielomian &v);
	friend Wielomian operator * (const Wielomian &u, const Wielomian &v);
	friend Wielomian operator * (const Wielomian &u, double c);
	Wielomian& operator += (const Wielomian &v);
	Wielomian& operator -= (const Wielomian &v);
	Wielomian& operator *= (const Wielomian &v);
	Wielomian& operator *= (double c);
	double operator () (double x) const; // obliczenie wartoœci wielomianu
	double operator [] (int i) const; // odczytanie i-tego wspó³czynnika

	void odczyt();
	void odczyt_stopien();
	void odczyt_wspolczynnik(int w);
	void zmien_wspolczynnik(int i, double nowy_wsp);

private:
	int n; //stopien wielomianu
	double *a; //wspolczynniki wielomianu
};

