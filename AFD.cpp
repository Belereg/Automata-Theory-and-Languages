#include "libraries.h"

#if 1

ifstream fin("date.txt");

int pozitie(char c, char* alf)
{
	for (int i = 0; i < strlen(alf); i++)
		if (c == alf[i])
			return i;
	return -1;
}

int main()
{
	int matrice[50][50], stare[50], stare_finala[50], nr_stari, nr_litere, stare_initiala, stare_curenta, nr_teste, stare_urmatoare, nr_stari_finale, pos, adv = 0;
	char alfabet[50], test[100], lambda = ':';
	fin >> nr_stari;

	for (int i = 0; i < nr_stari; i++)
		fin >> stare[i];

	fin >> stare_initiala;
	fin >> nr_litere;

	for (int i = 0; i < nr_litere; i++)
		fin >> alfabet[i];
	alfabet[nr_litere] = '\0';

	fin >> nr_stari_finale;
	for (int i = 0; i < nr_stari_finale; i++)
		fin >> stare_finala[i];

	for (int i = 0; i < nr_stari; i++)
		for (int j = 0; j < nr_litere; j++)
			fin >> matrice[i][j];

	for (int i = 0; i < nr_stari_finale; i++)
		if (stare_finala[i] == stare_initiala)
			adv = 1;

	fin >> nr_teste;
	int OK = 0;
	for (int i = 0; i < nr_teste; i++)
	{
		OK = 0;
		stare_curenta = stare_initiala;
		fin >> test;
		if (strcmp(test, ":") == 0 && adv == 1)
			OK = 2;
		else
		{
			for (int index = 0; index < strlen(test); index++)
			{
				pos = pozitie(test[index], alfabet);
				stare_urmatoare = matrice[stare_curenta][pos];
				stare_curenta = stare_urmatoare;
				if (stare_curenta == -1)
					break;
			}
			if (stare_curenta == -1)
				OK = 0;
			else
			{
				for (int i = 0; i < nr_stari_finale; i++)
					if (stare_curenta == stare_finala[i])
						OK = 1;
			}
		}
		if (OK == 1)
			cout << "Cuvantul " << test << " ESTE bun" << "\n\n";
		else if (OK == 0)
		{
			if (strcmp(test,":")==0)
				cout << "Cuvantul vid (Lambda, reprezentat cu ajutoru caracterului ':') NU este bun\n\n";
			else
				cout << "Cuvantul " << test << " NU e bun" << "\n\n";
		}
		else if (OK == 2)
			cout << "Cuvantul vid (Lambda, reprezentat cu ajutoru caracterului ':') este bun\n\n";
	}
	system("pause");
}
#endif