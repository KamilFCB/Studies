#include "stdafx.h"
#include "Wymierna.h"

using namespace wym;

Wymierna::Wymierna()
{
}

Wymierna::Wymierna(int licznik, int mianownik)
{
	try
	{
		if (mianownik == 0)
			throw mianownik_rowny_0();
		else if (licznik > INT_MAX || mianownik > INT_MAX)
			throw przekroczenie_zakresu();
		else
		{
			int dzielnik = nwd(licznik, mianownik);
			licz = licznik/dzielnik;
			mian = mianownik/dzielnik;
			if (mian < 0)
			{
				licz *= -1;
				mian *= -1;
			}
		}
	}
	catch (wyjatek_wymierny &err)
	{
		err.wypisz();
	}	
}

Wymierna::Wymierna(int licznik)
{
	licz = licznik;
	mian = 1;
}

Wymierna::Wymierna(const Wymierna &w)
{
	licz = w.licz;
	mian = w.mian;
}

Wymierna& Wymierna::operator = (const Wymierna &w)
{
	if (this == &w)
		return *this;
	
	licz = w.licz;
	mian = w.mian;

	return *this;
}

Wymierna::~Wymierna()
{
}

int Wymierna::licznik()
{
	return licz;
}

int Wymierna::mianownik()
{
	return mian;
}

void Wymierna::skroc()
{
	int a = nwd(licz, mian);

	licz /= a;
	mian /= a;
}

void Wymierna::mian_dodatni()
{
	if (mian < 0)
	{
		licz *= -1;
		mian *= -1;
	}
}

int Wymierna::nwd(int a, int b)
{
	int pom;

	while (b != 0)
	{
		pom = b;
		b = a%b;
		a = pom;
	}

	return a;
}

int Wymierna::nww(int a, int b)
{
	return (a*b) / nwd(a, b);
}

Wymierna wym::operator +(Wymierna &l, Wymierna &m)
{
	try
	{
		int nww = l.nww(l.mianownik(), m.mianownik());

		int tmp1 = nww / l.mianownik();
		int tmp2 = nww / m.mianownik();

		if (l.licznik() * tmp1 + m.licznik() * tmp2 > INT_MAX)
			throw przekroczenie_zakresu();
		else
		{
			int licznik = l.licznik() * tmp1 + m.licznik() * tmp2;

			Wymierna liczba = Wymierna(licznik, nww);
			liczba.skroc();
			liczba.mian_dodatni();

			return liczba;
		}
	}
	catch (wyjatek_wymierny &err)
	{
		err.wypisz();
	}
}

Wymierna wym::operator -(Wymierna &l, Wymierna &m)
{
	try
	{
		int nww = l.nww(l.mianownik(), m.mianownik());

		int tmp1 = nww / l.mianownik();
		int tmp2 = nww / m.mianownik();

		if (l.licznik() * tmp1 - m.licznik() * tmp2 > INT_MAX)
			throw przekroczenie_zakresu();
		else
		{
			int licznik = l.licznik() * tmp1 - m.licznik() * tmp2;

			Wymierna liczba = Wymierna(licznik, nww);
			liczba.skroc();
			liczba.mian_dodatni();

			return liczba;
		}
	}
	catch (wyjatek_wymierny &err)
	{
		err.wypisz();
	}
}

Wymierna wym::operator *(Wymierna &l, Wymierna &m)
{
	try
	{
		if (l.mianownik() == 0 || m.mianownik() == 0)
			throw dzielenie_przez_0();
		else if (l.licznik() * m.licznik() > INT_MAX || l.mianownik() * m.mianownik() > INT_MAX)
			throw przekroczenie_zakresu();
		else
		{
			int licznik = l.licznik() * m.licznik();
			int mianownik = l.mianownik() * m.mianownik();

			Wymierna liczba = Wymierna(licznik, mianownik);
			liczba.skroc();
			liczba.mian_dodatni();

			return liczba;
		}
	}
	catch (wyjatek_wymierny &err)
	{
		err.wypisz();
	}
}

Wymierna wym::operator /(Wymierna &l, Wymierna &m)
{
	try
	{
		if (m.licznik() == 0 || l.mianownik() == 0)
			throw dzielenie_przez_0();
		else if (l.licznik() * m.mianownik() > INT_MAX || l.mianownik() * m.licznik() > INT_MAX)
			throw przekroczenie_zakresu();
		else
		{
			int licznik = l.licznik() * m.mianownik();
			int mianownik = l.mianownik() * m.licznik();

			Wymierna liczba = Wymierna(licznik, mianownik);
			liczba.skroc();
			liczba.mian_dodatni();

			return liczba;
		}
	}
	catch (wyjatek_wymierny &err)
	{
		err.wypisz();
	}
	
}

Wymierna wym::operator -(Wymierna &l)
{
	int licznik = l.licznik()  * -1;
	int mianownik = l.mianownik();

	Wymierna liczba = Wymierna(licznik, mianownik);

	return liczba;
}

Wymierna wym::operator !(Wymierna &l)
{
	try
	{
		if (l.licznik() == 0)
			throw licznik_rowny_0();
		else
		{
			int mianownik = l.licznik();
			int licznik = l.mianownik();

			Wymierna liczba = Wymierna(licznik, mianownik);
			liczba.mian_dodatni();

			return liczba;
		}
	}
	catch (wyjatek_wymierny &err)
	{
		err.wypisz();
	}
}

std::ostream& wym::operator<< (std::ostream &wyj, const Wymierna &w)
{
	double wynik = double(w.licz) / double(w.mian);
	wyj << wynik;
	std::cout << std::endl;
	return wyj;
}

Wymierna::operator int() const
{
	return int(licz / mian);
}

Wymierna::operator double() const
{
	return double(licz) / double(mian);
}