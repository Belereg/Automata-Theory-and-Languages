#include "libraries.h"

struct NonTerminal
{
	int nrp;
	char non_terminal, prod[20][200];
};

struct Nod
{
	char str[200];
	Nod* fiu[100];
};

int nrNT;
bool ok;
NonTerminal NT[50];

bool verificare(Nod* rad, char cuv[])
{
	if (strcmp(rad->str, cuv) == 0 || ok || (strlen(rad->str) == 0 && strcmp(cuv, ".") == 0))
	{
		ok = true;
		return true;
	}

	int cnt = 0, cntNT = 0;

	for (int i = 0; i < strlen(rad->str); i++)
		if (rad->str[i] >= 'a' && rad->str[i] <= 'z')
			cnt++;

	for (int i = 0; i < strlen(rad->str); i++)
		if (rad->str[i] >= 'A' && rad->str[i] <= 'Z')
			cntNT++;

	if (cnt > strlen(cuv) || cntNT > 7)
		return false;

	for (int i = 0; i < strlen(rad->str) && !ok; i++)
		if (rad->str[i] >= 'A' && rad->str[i] <= 'Z')
			for (int j = 0; j < nrNT && !ok; j++)
				if (NT[j].non_terminal == rad->str[i])
					for (int z = 0; z < NT[j].nrp && !ok; z++)
					{
						rad->fiu[z] = new Nod;

						strcpy(rad->fiu[z]->str, rad->str);

						char aux[200];
						strcpy(aux, rad->fiu[z]->str + i + 1);

						if (NT[j].prod[z][0] == '.')
						{
							strcpy(rad->fiu[z]->str + i, aux);
						}
						else
						{
							strcpy(rad->fiu[z]->str + i, NT[j].prod[z]);
							strcpy(rad->fiu[z]->str + strlen(rad->fiu[z]->str), aux);
						}
						verificare(rad->fiu[z], cuv);
					}

	if (ok)
		return true;
	return false;
}

int main()
{
	ifstream fin("gic.in");
	char begNT;

	fin >> nrNT >> begNT;

	for (int i = 0; i < nrNT; i++)
	{
		fin >> NT[i].non_terminal >> NT[i].nrp;

		for (int j = 0; j < NT[i].nrp; j++)
			fin >> NT[i].prod[j];

	}
	Nod* rad = new Nod;

	rad->str[0] = begNT;
	rad->str[1] = '\0';

	char cuv_verif[200], yn;
	do
	{
		ok = false;
		cout << "Cuvant de verificat: ";
		cin >> cuv_verif;

		if (verificare(rad, cuv_verif))
			cout << "Acceptat.";
		else
			cout << "Neacceptat.";

		cout << "\n\nContinuati(y/n)? ";
		cin >> yn;
		cout << endl;
	} while (yn == 'y');

  system("pause"); //return 0;
}
