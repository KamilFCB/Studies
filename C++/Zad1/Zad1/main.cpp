#include <iostream>
#include <string>

using namespace std;

const int B[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
const std::string R[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };


unsigned long long int arab2bin(const char *x);
string bin2rzym(int x);


int main(int argc, char **argv)
{
	for(int i=1; i<argc; i++)
	{
		unsigned long long int wynik = arab2bin(argv[i]);
		if (wynik == 0)
		{
			cerr << "Bledne dane" << endl;
			continue;
		}

		string wyn = bin2rzym(wynik);
		cout << "Liczba rzymska: " << wyn << " to dziesietnie: " << argv[i] << endl;
	}

	return 0;
}

unsigned long long int arab2bin(const char *x)
{
	int dlugosc = strlen(x);

	if (x[0] == '0')
		return 0;
	if (dlugosc > 4)
		return 0;
	for (int i = 0; i < dlugosc; i++)
	{
		if (x[i] < '0' || x[i] > '9')
			return 0;
	}

	return stoi(x);	
}

string bin2rzym(int x)
{
	string bin = to_string(x);
	string wynik;
	int dziesietna = strtol(bin.c_str(), NULL, 2);
	int j = 0;
	while (dziesietna > 0)
	{
		if (dziesietna - B[j] >= 0)
		{
			wynik += R[j];
			dziesietna -= B[j];
			j = 0;
		}
		else
			j++;
	}

	return wynik;
}
