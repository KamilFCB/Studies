// Zad3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Kolejka.h"
#include <utility>
#include <Windows.h>


int main()
{
	int rozmiar, flaga=0;
	string slowo;
	cout << "Podaj rozmiar kolejki" << endl;
	cin >> rozmiar;
	Kolejka *k = new Kolejka(rozmiar);
	while (flaga != 7)
	{
		system("cls");
		cout << "[1] Dodaj nowy element do kolejki" << endl;
		cout << "[2] Sprawdz ilosc elementow w kolejce" << endl;
		cout << "[3] Sprawdz pojemnosc kolejki" << endl;
		cout << "[4] Pobierz pierwszy element" << endl;
		cout << "[5] Sprawdz pierwszy element" << endl;
		cout << "[6] Wypisz wszystkie elementy kolejki" << endl;
		cout << "[7] Zakoncz" << endl;
		cin >> flaga;

		switch (flaga)
		{
		case 1:
			system("cls");
			cout << "Podaj wartosc" << endl;
			cin >> slowo;
			try
			{
				k->wstaw(slowo);
			}
			catch (string w)
			{
				cout << w << endl;
				Sleep(1000);
			}
			break;
		case 2:
			system("cls");
			cout << k->rozmiar() << endl;
			Sleep(1000);
			break;
		case 3:
			system("cls");
			cout << k->pojemnosc_k() << endl;
			Sleep(1000);
			break;
		case 4:
			system("cls");
			slowo = k->pobierz();
			cout << "Wartosc zostala pobrana" << endl;
			Sleep(1000);
			break;
		case 5:
			system("cls");
			cout << k->sprawdz() << endl;
			Sleep(1000);
			break;
		case 6:
			system("cls");
			k->wypisz();
			Sleep(2000);
			break;
		case 7:
			flaga = 7;
			break;
			
		}
	}
	
	cout << "--------------------------------" << endl;
	Kolejka k1(5);
	k1.wstaw("slowo");
	cout << "Kolejka zainicjowana z podaniem pojemnosci" << endl;
	k1.wypisz();
	cout << "Pojemnosc / Rozmiar: " << k1.pojemnosc_k() << " / " << k1.rozmiar() << endl;

	cout << "--------------------------------" << endl;
	Kolejka *k2 = new Kolejka();	
	k2->wstaw("slowo2");
	cout << "Kolejka zainicjowana bez podania rozmiaru" << endl;
	k2->wypisz();
	cout << "Pojemnosc / Rozmiar: " << k2->pojemnosc_k() << " / " << k2->rozmiar() << endl;

	cout << "--------------------------------" << endl;
	Kolejka k3(k1);
	cout << "Kopia pierwszej kolejki" << endl;
	k3.wypisz();
	cout << "Pojemnosc / Rozmiar: " << k3.pojemnosc_k() << " / " << k3.rozmiar() << endl;

	cout << "--------------------------------" << endl;
	Kolejka k4 = { "jeden", "dwa", "trzy" };
	cout << "Kopia pierwszej kolejki" << endl;
	k4.wypisz();
	cout << "Pojemnosc / Rozmiar: " << k4.pojemnosc_k() << " / " << k4.rozmiar() << endl;

	cout << "--------------------------------" << endl;
	Kolejka k5(*k2);
	cout << "Kolejka stworzona z przeniesienia drugiej kolejki" << endl;
	k5.wypisz();
	cout << "Pojemnosc / Rozmiar: " << k5.pojemnosc_k() << " / " << k5.rozmiar() << endl;

	system("pause");
    return 0;
}

