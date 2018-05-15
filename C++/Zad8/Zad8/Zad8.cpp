// Zad8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "bst.h"
#include <Windows.h>

using namespace std;
using namespace struktury;


int main()
{
	/*bst <int>*b = new bst<int>();
	int v,t;
	while (1)
	{
		cout << "1. Dodaj" << endl;
		cout << "2. Wypisz" << endl;
		cout << "3. Znajdz" << endl;
		cout << "4. Usun" << endl;
		cout << "5. Zakoncz" << endl;
		cin >> t;
		
		switch (t)
		{
		case 1:
			cout << "Podaj wartosc" << endl;
			cin >> v;
			b->insert(v);
			system("cls");
			break;
		case 2:
			b->print();
			Sleep(2000);
			system("cls");
			break;
		case 3:
			cout << "Podaj wartosc" << endl;
			cin >> v;
			if (b->search(v))
				cout << "Znaleziono" << endl;
			else cout << "Nie znaleziono" << endl;
			Sleep(2000);
			system("cls");
			break;
		case 4:
			cout << "Podaj wartosc" << endl;
			cin >> v;
			b->remove(v);
			system("cls");
			break;
		case 5:
			delete b;
			system("pause");
			return 0;
			break;
		}
	}*/

	string tab[1] = { "elo" };
	
	for (int i = 0; i<3; i++) {
		cout << tab[0][i] << endl;
	}


	system("pause");
    return 0;
}

