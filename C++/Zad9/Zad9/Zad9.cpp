// Zad9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "PlikWejsciowy.h"
#include "PlikWyjsciowy.h"

using namespace std;


class index
{
private:
	int x, w;
public:
	friend ostream& operator <<(ostream &os, const index &in)
	{
		string res = "[";
		int i = in.w;
		for (; i > 0; i--)
			res += " ";
		res += to_string(in.x);		
		res += "]";
		return os << res;
	};
	index(int a, int b) : x(a), w(b) {};
};

inline ostream& comma(ostream &os)
{ 
	return os << ", "; 
}

inline ostream& colon(ostream &os)
{
	return os << ": ";
}

inline istream& clearline(istream &is)
{
	cout << "elo";
	return is;
}


int main()
{
	/*int x = 1;
	cout << "x:" << comma << x << endl;
	cout << index(1, 3) << endl;
	string s;

	cin >> clearline >> s;
	cout << s;*/
	PlikWejsciowy *p = new PlikWejsciowy("plik.txt");
	p->printLine();
	p->printLine();
	system("pause");
    return 0;
}

