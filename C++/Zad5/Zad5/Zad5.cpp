// Zad5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Lista.h"

using namespace std;

int main()
{
	Lista tmp(1);
	
	tmp.pierwszy->dodaj(2, 0);
	cout << "-------" << endl;
	//tmp.wypisz();

	

	system("pause");
    return 0;
}

