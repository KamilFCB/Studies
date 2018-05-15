#pragma once
#include "Wyj¹tki.h"
#include<iostream>

namespace wym
{
	class Wymierna
	{
	public:
		Wymierna();
		Wymierna(int licznik, int mianownik) throw(mianownik_rowny_0, przekroczenie_zakresu);
		Wymierna(int licznik);
		Wymierna& operator = (const Wymierna &w);
		Wymierna(const Wymierna &w);
		~Wymierna();
		int licznik();
		int mianownik();
		void mian_dodatni();
		void skroc();
		int nwd(int a, int b);
		int nww(int a, int b);

		friend Wymierna operator +(Wymierna &l, Wymierna &m) throw(przekroczenie_zakresu);
		friend Wymierna operator -(Wymierna &l, Wymierna &m) throw(przekroczenie_zakresu);
		friend Wymierna operator *(Wymierna &l, Wymierna &m) throw(dzielenie_przez_0, przekroczenie_zakresu);
		friend Wymierna operator /(Wymierna &l, Wymierna &m) throw(dzielenie_przez_0, przekroczenie_zakresu);
		friend Wymierna operator -(Wymierna &l);
		friend Wymierna operator !(Wymierna &l) throw(licznik_rowny_0);
		friend std::ostream& operator<< (std::ostream &wyj, const Wymierna &w);
		operator int() const;
		operator double() const;


	private:
		int licz, mian;

	};
}

