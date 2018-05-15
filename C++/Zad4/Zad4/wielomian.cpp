#include "stdafx.h"
#include "wielomian.h"


Wielomian::Wielomian()
{
}

Wielomian::Wielomian(int st, double wsp)
{
	n = st;
	a = new double[n+1];
	a[n] = wsp;
}

Wielomian::Wielomian(int st, const double wsp[])
{
	n = st;
	a = new double[st+1];
	for (int i = st; i >=0; i--)
	{
		a[i] = wsp[i];
	}
}

Wielomian::Wielomian(initializer_list<double> wsp)
{
	a = new double[wsp.size()];
	int i = wsp.size()-1;
	for (auto it = wsp.end()-1; it != wsp.begin(); --it)
	{
		a[i] = *it;
		i--;
	}
	n = wsp.size()-1;
}

Wielomian::Wielomian(const Wielomian &w)
{
	a = new double[w.n+1];
	for (int i = 0; i <= w.n; i++)
		a[i] = w.a[i];
	n = w.n;

}

Wielomian::Wielomian(Wielomian &&w)
{
	a = w.a;
	w.a = nullptr;
	n = w.n;
}

Wielomian& Wielomian::operator = (const Wielomian &w)
{
	if (this == &w)
		return *this;
	for (int i = 0; i <= w.n; i++)
		a[i] = w.a[i];

	return *this;
}

Wielomian& Wielomian::operator = (Wielomian &&w)
{
	delete[] a;
	a = w.a;
	w.a = nullptr;
	n = w.n;

	return *this;
}

Wielomian::~Wielomian()
{
	delete[] a;
}

void Wielomian::odczyt()
{
	int j = 0;
	for(int i=n; i>=0; i--, j++)
		cout << a[i] << "x^" << n-j << " ";
	cout << endl;
}

void Wielomian::odczyt_stopien()
{
	cout << n << endl;
}

void Wielomian::odczyt_wspolczynnik(int w)
{
	cout << a[w] << endl;
}

void Wielomian::zmien_wspolczynnik(int i, double nowy_wsp)
{
	if (i == n && n != 0 && nowy_wsp == 0)
		throw string("Nie mozna ustawic wspolczynnika przy najwyzszej potedze na 0");
	else if (i > n || i < 0)
		throw string("Nie mozna ustawic wspolczynnika przy stopniu wiekszym od stopnia wielomianu lub stopniu ujemnym");
	else
		a[i] = nowy_wsp;
}

istream& operator >> (istream &we, Wielomian &w)
{
	for (int i = 0; i <= w.n; i++)
		we >> w.a[i];

	return we;
}

ostream& operator << (ostream &wy, const Wielomian &w)
{
	int j = 0;
	for (int i = w.n; i >= 0; i--, j++)
		wy << w.a[i] << "x^" << w.n - j << " ";
	cout << endl;
	return wy;
}


Wielomian operator + (const Wielomian &u, const Wielomian &v)
{
	int stopien = max(u.n, v.n);
	int min = (u.n < v.n) ? u.n : v.n;
	double *tab = new double[stopien+1];
	for (int i = 0; i <= stopien; i++)
		tab[i] = 0;

	for (int i = 0; i <= min; i++)
	{
		tab[i] = u.a[i] + v.a[i];
	}

	if (u.n > v.n)
	{
		for (int i = min + 1; i <= stopien; i++)
			tab[i] = u.a[i];
	}
	else
	{
		for (int i = min + 1; i <= stopien; i++)
			tab[i] = v.a[i];
	}

	Wielomian w(stopien, tab);
	delete[] tab;
	return w;
}

Wielomian operator - (const Wielomian &u, const Wielomian &v)
{
	int stopien = max(u.n, v.n);
	int min = (u.n < v.n) ? u.n : v.n;
	double *tab = new double[stopien+1];

	for (int i = 0; i <=min; i++)
	{
		tab[i] = u.a[i] - v.a[i];
	}
	
	if (u.n > v.n)
	{
		for (int i = min+1; i <= stopien; i++)
			tab[i] = u.a[i];
	}
	else
	{
		for (int i = min+1; i <= stopien; i++)
			tab[i] = 0 - v.a[i];
	}


	Wielomian w(stopien, tab);
	return w;
}

Wielomian operator *(const Wielomian &u, const Wielomian &v)
{
	int stopien = u.n + v.n;
	double *tab = new double[stopien+1];
	for (int i = 0; i <= stopien; i++)
		tab[i] = 0;

	for (int i = 0; i <= u.n; i++)
	{
		for (int j = 0; j <= v.n; j++)
		{
			tab[i + j] += u.a[i] * v.a[j];
		}
	}

	Wielomian w(stopien, tab);
	return w;
}

Wielomian operator * (const Wielomian &u, double c)
{
	int stopien = u.n;
	double *tab = new double[stopien+1];
	for (int i = 0; i <= stopien; i++)
		tab[i] = u.a[i] * c;

	Wielomian w(stopien, tab);
	return w;
}

Wielomian& Wielomian::operator += (const Wielomian &v)
{
	if (n < v.n)
	{
		int i = 0;
		double *tab = new double[v.n+1];
		for (; i <= n; i++)
			tab[i] = a[i] + v.a[i];
		for (; i <= v.n; i++)
			tab[i] = v.a[i];
		delete[] a;
		a = tab;
		n = v.n;
	}
	else
	{
		for (int i = 0; i <= n; i++)
			a[i] += v.a[i];
	}

	return *this;
}

Wielomian& Wielomian::operator -= (const Wielomian &v)
{
	if (n < v.n)
	{
		int i = 0;
		double *tab = new double[v.n + 1];
		for (; i <= n; i++)
			tab[i] = a[i] - v.a[i];
		for (; i <= v.n; i++)
			tab[i] = -v.a[i];

		n = v.n;
		delete[] a;
		a = tab;
	}
	else
	{
		for (int i = 0; i <= n; i++)
			a[i] -= v.a[i];
	}

	return *this;
}

Wielomian& Wielomian::operator *= (const Wielomian &v)
{
	int stopien = n + v.n;
	double *tab = new double[stopien+1];
	for (int i = 0; i <= stopien; i++)
		tab[i] = 0;

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= v.n; j++)
		{
			tab[i + j] += a[i] * v.a[j];
		}
	}

	delete[] a;
	a = tab;
	n = stopien;	

	return *this;
}

Wielomian& Wielomian::operator *= (double c)
{
	for (int i = 0; i <= n; i++)
		a[i] *= c;

	return *this;
}

double Wielomian::operator () (double x) const
{
	double wynik = a[n];

	for (int i = n-1; i >= 0; i--)
		wynik = wynik*x + a[i];

	return wynik;
}

double Wielomian::operator [] (int i) const
{
	return a[i];
}