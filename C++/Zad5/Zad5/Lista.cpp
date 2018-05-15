#include "stdafx.h"
#include "Lista.h"

Lista::Wezel *pierwszy, *ostatni;

Lista::Lista()
{
	pierwszy = new Wezel;
	ostatni = new Wezel;
}

Lista::Lista(int v)
{
	Wezel *nowy = new Wezel();
	nowy->next = nullptr;
	nowy->prev = nullptr;
	nowy->val = v;
	pierwszy = nowy;
	ostatni = nowy;
}


Lista::~Lista()
{
}

Lista::Wezel::Wezel()
{

}

Lista::Wezel::Wezel(double v)
{
	prev = nullptr;
	next = nullptr;
	val = v;
}

Lista::Wezel::~Wezel()
{
}

void Lista::wypisz()
{
	Wezel *tmp = pierwszy;
	while (tmp != nullptr)
	{
		cout << tmp->val << endl;
		tmp = tmp->next;
	}
}

void Lista::Wezel::dodaj(double v, int poz)
{
	Wezel *nowy = new Wezel(v);
	
	/*if (poz == 0)
	{
		nowy->next = ::pierwszy;
		nowy->prev = nullptr;
		::pierwszy->prev = nowy;
		::pierwszy = nowy;
		
		
	}
	else if (poz == 1)
	{
		nowy->prev = this;
		nowy->next = nullptr;
		::ostatni = nowy;
		::pierwszy->next = nowy;
		
	}*/
	//else
	//{
	//	for (int i = 0; i != poz && tmp != nullptr; i++)
	//		tmp = tmp->next;
	//	
	//	tmp->prev->next = nowy;
	//	tmp->prev = nowy;
	//	nowy->next = tmp;
	//	nowy->prev = tmp->prev;
	//}
	cout << ::pierwszy->val;
	Wezel *tmp1 = ::pierwszy;
	while (tmp1 != nullptr)
	{
		cout << tmp1->val << endl;
		tmp1 = tmp1->next;
	}


}

