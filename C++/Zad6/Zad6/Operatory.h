#pragma once
#include "Wyrazenie.h"
#include <math.h>
#include <iostream>

class Operator1Arg : public Wyrazenie
{
public:
	Operator1Arg(Wyrazenie *arg);
	Operator1Arg();
	~Operator1Arg();

	virtual std::string opis();
	virtual double oblicz();

	Wyrazenie *arg1;
};

class Sin : public Operator1Arg
{
public:
	Sin(Wyrazenie *arg1);
	Sin();
	~Sin();

	std::string opis() override;
	double oblicz() override;
};

class Cos : public Operator1Arg
{
public:
	Cos(Wyrazenie *arg1);
	Cos();
	~Cos();

	std::string opis() override;
	double oblicz() override;
};

class Exp : public Operator1Arg
{
public:
	Exp(Wyrazenie *arg1);
	Exp();
	~Exp();

	std::string opis() override;
	double oblicz() override;
};

class Ln : public Operator1Arg
{
public:
	Ln(Wyrazenie *arg1);
	Ln();
	~Ln();

	std::string opis() override;
	double oblicz() override;
};

class Bezwzgl : public Operator1Arg
{
public:
	Bezwzgl(Wyrazenie *arg1);
	Bezwzgl();
	~Bezwzgl();

	std::string opis() override;
	double oblicz() override;
};

class Przeciw : public Operator1Arg
{
public:
	Przeciw(Wyrazenie *arg1);
	Przeciw();
	~Przeciw();

	std::string opis() override;
	double oblicz() override;
};

class Odwrot : public Operator1Arg
{
public:
	Odwrot(Wyrazenie *arg1);
	Odwrot();
	~Odwrot();

	std::string opis() override;
	double oblicz() override;
};



class Operator2Arg : public Operator1Arg
{
public:
	Operator2Arg(Wyrazenie *arg);
	Operator2Arg();
	~Operator2Arg();

	virtual std::string opis();
	virtual double oblicz();

	Wyrazenie *arg2;
};

class Dodaj : public Operator2Arg
{
public:
	Dodaj(Wyrazenie *argx, Wyrazenie *argy);
	Dodaj();
	~Dodaj();

	std::string opis() override;
	double oblicz() override;

	Wyrazenie *arg2;
};

class Odejmij : public Operator2Arg
{
public:
	Odejmij(Wyrazenie *arg1, Wyrazenie *arg2);
	Odejmij();
	~Odejmij();

	std::string opis() override;
	double oblicz() override;
};

class Mnoz : public Operator2Arg
{
public:
	Mnoz(Wyrazenie *arg1, Wyrazenie *arg2);
	Mnoz();
	~Mnoz();

	std::string opis() override;
	double oblicz() override;
};

class Dziel : public Operator2Arg
{
public:
	Dziel(Wyrazenie *arg1, Wyrazenie *arg2);
	Dziel();
	~Dziel();

	std::string opis() override;
	double oblicz() override;
};

class Logarytm : public Operator2Arg
{
public:
	Logarytm(Wyrazenie *arg1, Wyrazenie *arg2);
	Logarytm();
	~Logarytm();

	std::string opis() override;
	double oblicz() override;
};

class Modulo : public Operator2Arg
{
public:
	Modulo(Wyrazenie *arg1, Wyrazenie *arg2);
	Modulo();
	~Modulo();

	std::string opis() override;
	double oblicz() override;
};

class Potega : public Operator2Arg
{
public:
	Potega(Wyrazenie *arg1, Wyrazenie *arg2);
	Potega();
	~Potega();

	std::string opis() override;
	double oblicz() override;
};