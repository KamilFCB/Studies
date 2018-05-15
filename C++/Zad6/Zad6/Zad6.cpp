// Zad6.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Operandy.h"
#include "Operatory.h"


using namespace std;

vector<pair<string, double>> Zmienna::val;

int main()
{
	Zmienna *x = new Zmienna("x");
	x->dodaj(1, "x", 0);
	x->dodaj(2, "x", 0);
	
	// cos((x+1)*x)/e^x^2

	Wyrazenie *w = new Dziel(
		new Cos(
			new Mnoz(
				new Dodaj(
					x,
					new Liczba(1)
				),
				x
			)
		),
		new Potega(
			new Potega(
				new E(),
				x
			),
			new Liczba(2)
		)
	);
	cout << endl;
	cout << w->opis() << endl;

	for (double i = 0.01; i <= 1.01; i += 0.01)
	{
		w = new Dziel(
			new Cos(
				new Mnoz(
					new Dodaj(
						new Zmienna("x"),
						new Liczba(1)
					),
					new Zmienna("x")
				)
			),
			new Potega(
				new Potega(
					new E(),
					new Zmienna("x")
				),
				new Liczba(2)
			)
		);
		cout << w->oblicz() << endl;
		x->zmien_wartosc(i);

	}

	// 2+x*7-(y*3+5)
	x->licznik = 0;
	x->dodaj(1, "y", 0);
	x->dodaj(0, "x", 0);
	w = new Odejmij(
		new Dodaj(
			new Liczba(2),
			new Mnoz(
				x,
				new Liczba(7)
			)
		),
		new Dodaj(
			new Mnoz(
				x,
				new Liczba(3)
			),
			new Liczba(5)
		)
	);
	cout << endl;
	cout << w->opis() << endl;
	for (double i = 0.01; i <= 1.01; i += 0.01)
	{
		w = new Odejmij(
			new Dodaj(
				new Liczba(2),
				new Mnoz(
						new Zmienna("x"),
						new Liczba(7)
					)
				),
			new Dodaj(
				new Mnoz(
					new Zmienna("y"),
					new Liczba(3)
				),
				new Liczba (5)
			)
		);
		cout << w->oblicz() << endl;
		x->zmien_wartosc(i);

	}

	// (3+5)/(2+x*7)
	x->licznik = 0;
	x->dodaj(0, "x", 0);
	w = new Dziel(
			new Dodaj(
				new Liczba(3),
				new Liczba(5)
			),
			new Dodaj(
				new Liczba(2),
				new Mnoz(
					x,
					new Liczba(7)
				)
			)
	);
	cout << endl;
	cout << w->opis() << endl;
	for (double i = 0.01; i <= 1.01; i += 0.01)
	{
		w = new Dziel(
			new Dodaj(
				new Liczba(3),
				new Liczba(5)
			),
			new Dodaj(
				new Liczba(2),
				new Mnoz(
					new Zmienna("x"),
					new Liczba(7)
				)
			)
		);
		cout << w->oblicz() << endl;
		x->zmien_wartosc(i);

	}
	
	// ((x-1)*x)/2
	
	x->licznik = 0;
	x->dodaj(0, "x", 0);
	x->dodaj(1, "x", 0);
	w = new Dziel(
		new Mnoz(
			new Odejmij(
				x,
				new Liczba(1)
			),
			x
		),
		new Liczba(2)
	);
	cout << endl;
	cout << w->opis() << endl;
	for (double i = 0.01; i <= 1.01; i += 0.01)
	{
		w = new Dziel(
			new Mnoz(
				new Odejmij(
					new Zmienna("x"),
					new Liczba(1)
				),
				new Zmienna("x")
			),
			new Liczba(2)
		);
		cout << w->oblicz() << endl;
		x->zmien_wartosc(i);
	}
	
	

	system("pause");
    return 0;
}

