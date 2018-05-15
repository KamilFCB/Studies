#include "stdafx.h"
#include "Operatory.h"


Operator1Arg::Operator1Arg(Wyrazenie *arg)
{
	arg1 = arg;	
}

Operator1Arg::Operator1Arg()
{}

Operator1Arg::~Operator1Arg()
{}

double Operator1Arg::oblicz()
{
	return arg1->oblicz();
}

std::string Operator1Arg::opis()
{
	return arg1->opis();
}

Operator2Arg::Operator2Arg(Wyrazenie *arg)
{
	arg2 = arg;
}

Operator2Arg::Operator2Arg()
{}

Operator2Arg::~Operator2Arg()
{}

double Operator2Arg::oblicz()
{
	return arg2->oblicz();
}

std::string Operator2Arg::opis()
{
	return arg2->opis();
}

Sin::Sin(Wyrazenie *arg)
{
	arg1 = new Operator1Arg(arg);
}

Sin::Sin()
{}

double Sin::oblicz()
{
	return sin(arg1->oblicz());
}

std::string Sin::opis()
{
	return "sin(" + arg1->opis() + ")";
}

Cos::Cos(Wyrazenie *arg)
{
	arg1 = new Operator1Arg(arg);
}

Cos::Cos()
{}

double Cos::oblicz()
{
	return cos(arg1->oblicz());
}

std::string Cos::opis()
{
	return "cos(" + arg1->opis() + ")";
}

Exp::Exp(Wyrazenie *arg)
{
	arg1 = new Operator1Arg(arg);
}

Exp::Exp()
{}

double Exp::oblicz()
{
	return exp(arg1->oblicz());
}

std::string Exp::opis()
{
	return "exp(" + arg1->opis() + ")";
}

Ln::Ln(Wyrazenie *arg)
{
	arg1 = new Operator1Arg(arg);
}

Ln::Ln()
{}

double Ln::oblicz()
{
	return log(arg1->oblicz());
}

std::string Ln::opis()
{
	return "ln(" + arg1->opis() + ")";
}

Bezwzgl::Bezwzgl(Wyrazenie *arg)
{
	arg1 = new Operator1Arg(arg);
}

Bezwzgl::Bezwzgl()
{}

double Bezwzgl::oblicz()
{
	return abs(arg1->oblicz());
}

std::string Bezwzgl::opis()
{
	return "abs(" + arg1->opis() + ")";
}

Przeciw::Przeciw(Wyrazenie *arg)
{
	arg1 = new Operator1Arg(arg);
}

Przeciw::Przeciw()
{}

double Przeciw::oblicz()
{
	return arg1->oblicz() * -1;
}

std::string Przeciw::opis()
{
	if (arg1->oblicz() >= 0)
		return "-" + arg1->opis();

	return arg1->opis();
}

Odwrot::Odwrot(Wyrazenie *arg)
{
	arg1 = new Operator1Arg(arg);
}

Odwrot::Odwrot()
{}

double Odwrot::oblicz()
{
	return 1 / arg1->oblicz();
}

std::string Odwrot::opis()
{
	return "1/" + arg1->opis();
}

Dodaj::Dodaj(Wyrazenie *argx, Wyrazenie *argy)
{
	arg1 = new Operator1Arg(argx);
	arg2 = new Operator2Arg(argy);
}

Dodaj::Dodaj()
{}

double Dodaj::oblicz()
{
	return arg1->oblicz() + arg2->oblicz();
}

std::string Dodaj::opis()
{
	return arg1->opis() + "+" + arg2->opis();
}

Odejmij::Odejmij(Wyrazenie *argx, Wyrazenie *argy)
{
	arg1 = new Operator1Arg(argx);
	arg2 = new Operator2Arg(argy);
}

Odejmij::Odejmij()
{}

double Odejmij::oblicz()
{
	return arg1->oblicz() - arg2->oblicz();
}

std::string Odejmij::opis()
{
	return arg1->opis() + "-" + arg2->opis();
}

Mnoz::Mnoz(Wyrazenie *argx, Wyrazenie *argy)
{
	arg1 = new Operator1Arg(argx);
	arg2 = new Operator2Arg(argy);
}

Mnoz::Mnoz()
{}

double Mnoz::oblicz()
{
	return arg1->oblicz() * arg2->oblicz();
}

std::string Mnoz::opis()
{
	return arg1->opis() + "*" + arg2->opis();
}

Dziel::Dziel(Wyrazenie *argx, Wyrazenie *argy)
{
	arg1 = new Operator1Arg(argx);
	arg2 = new Operator2Arg(argy);
}

Dziel::Dziel()
{}

double Dziel::oblicz()
{
	return arg1->oblicz() / arg2->oblicz();
}

std::string Dziel::opis()
{
	return arg1->opis() + "/" + arg2->opis();
}

Modulo::Modulo(Wyrazenie *argx, Wyrazenie *argy)
{
	arg1 = new Operator1Arg(argx);
	arg2 = new Operator2Arg(argy);
}

Modulo::Modulo()
{}

double Modulo::oblicz()
{
	return fmod(arg1->oblicz(),arg2->oblicz());
}

std::string Modulo::opis()
{
	return arg1->opis() + "%" + arg2->opis();
}

Potega::Potega(Wyrazenie *argx, Wyrazenie *argy)
{
	arg1 = new Operator1Arg(argx);
	arg2 = new Operator2Arg(argy);
}

Potega::Potega()
{}

double Potega::oblicz()
{
	return pow(arg1->oblicz(), arg2->oblicz());
}

std::string Potega::opis()
{
	return arg1->opis() + "^" + arg2->opis();
}

Logarytm::Logarytm(Wyrazenie *argx, Wyrazenie *argy)
{
	arg1 = new Operator1Arg(argx);
	arg2 = new Operator2Arg(argy);
}

Logarytm::Logarytm()
{}

double Logarytm::oblicz()
{
	return log(arg2->oblicz()) / log(arg1->oblicz());
}

std::string Logarytm::opis()
{
	return "log" + arg1->opis() + " " + arg2->opis();
}

Sin::~Sin()
{
	delete arg1;
}

Cos::~Cos()
{
	delete arg1;
}

Ln::~Ln()
{
	delete arg1;
}

Exp::~Exp()
{
	delete[] arg1;
}

Bezwzgl::~Bezwzgl()
{
	delete[] arg1;
}

Przeciw::~Przeciw()
{
	delete[] arg1;
}

Odwrot::~Odwrot()
{
	delete[] arg1;
}

Dodaj::~Dodaj()
{
	delete[] arg1;
	delete[] arg2;
}

Odejmij::~Odejmij()
{
	delete[] arg1;
	delete[] arg2;
}
Mnoz::~Mnoz()
{
	delete[] arg1;
	delete[] arg2;
}

Dziel::~Dziel()
{
	delete[] arg1;
	delete[] arg2;
}

Potega::~Potega()
{
	delete[] arg1;
	delete[] arg2;
}

Modulo::~Modulo()
{
	delete[] arg1;
	delete[] arg2;
}

Logarytm::~Logarytm()
{
	delete[] arg1;
	delete[] arg2;
}