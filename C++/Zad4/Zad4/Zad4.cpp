// Zad4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "wielomian.h"


int main()
{
	int stopien1;
	cout << "Podaj stopien pierwszego wielomianu" << endl;
	cin >> stopien1;
	double *wsp1 = new double[stopien1 + 1];
	cout << "Podaj wspolczynniki" << endl;
	for (int i = 0; i <= stopien1; i++)
		cin >> wsp1[i];

	int stopien2;
	cout << "Podaj stopien drugiego wielomianu" << endl;
	cin >> stopien2;
	double *wsp2 = new double[stopien2 + 1];
	cout << "Podaj wspolczynniki" << endl;
	for (int i = 0; i <= stopien2; i++)
		cin >> wsp2[i];

	Wielomian w1(stopien1, wsp1);
	Wielomian w2(stopien2, wsp2);

	cout << "Pierwszy: " << w1 << "Drugi: " << w2 << endl;

	cout << "Dodawanie: " << w1 + w2 << endl;
	cout << "Odejmowanie: " << w1 - w2 << endl;
	cout << "Mnozenie: " << w1 * w2 << endl;
	cout << "Pierwszy wielomian *4: " << w1 * 4 << endl;

	Wielomian w3 = w2 + w1;
	cout << w3;
	w3 -= w1;
	cout << w3;
	w3 *= w1;
	cout << w3;
	w3 *= 2;
	cout << w3;

	cout << "Wartosc pierwszego wielomianu dla x=4: " << w1(4) << endl;
	cout << "Pierwszy wspolczynnik drugiego wielomianu" << w2[1] << endl;

	system("pause");

    return 0;
}

