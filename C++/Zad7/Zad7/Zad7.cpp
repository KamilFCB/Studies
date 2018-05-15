// Zad7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Wymierna.h"
#include <iostream>

using namespace std;
using namespace wym;

int main()
{
	Wymierna x = Wymierna(1, 4);
	Wymierna y = Wymierna(4, 8);
	cout << x.licznik() << "/" << x.mianownik() << endl;
	cout << y.licznik() << "/" << y.mianownik() << endl;

	Wymierna z = x + y;
	cout << "Dodawanie: " << z.licznik() << "/" << z.mianownik() << endl;
	z = x - y;
	cout << "Odejmowanie: " << z.licznik() << "/" << z.mianownik() << endl;
	z = x * y;
	cout << "Mnozenie: " << z.licznik() << "/" << z.mianownik() << endl;
	z = x / y;
	cout << "Dzielenie: " << z.licznik() << "/" << z.mianownik() << endl;

	Wymierna t = Wymierna(1, -10);
	cout << "Wymierna(1,-10) " << t.licznik() << "/" << t.mianownik() << endl;
	t = -t;
	cout << "Wartosc przeciwna " << t.licznik() << "/" << t.mianownik() << endl;
	t = !t;
	cout << "Odwrotnosc " << t.licznik() << "/" << t.mianownik() << endl;

	Wymierna o = Wymierna(1, 0);
	cout << "Wymierna(1,0)" << endl;

	
	system("pause");
    return 0;
}

