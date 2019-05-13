#include "libraries.h"
ifstream fin("holyshit.txt");

#if 1
int pozitie(char c, char* alfabet)
{
	for (int i = 0; i < strlen(alfabet); i++)
		if (c == alfabet[i])
			return i;
	return -1;
}

bool find(int x, vector <int> vect)
{
	for (int i = 0; i < vect.size(); i++)
	{
		if (x == vect[i])
			return 1;
	}
	return 0;
}

bool same_or_not(vector<int> vect1, vector<int> vect2)
{
	if (vect1.size() != vect2.size())
		return 0;

	for (int i = 0; i < vect1.size(); i++)
		if (!find(vect1[i], vect2))
			return 0;
	return 1;
}

int ind_stari_finale(vector<int> * stari_noi, vector<int> vect, int nr_stari_noi)
{
	for (int i = 0; i < nr_stari_noi; i++)
	{
		if (same_or_not(vect, stari_noi[i]))
			return i;
	}
	return -1;
}

void find_e_closure(int x, vector<int> & closure, vector<int> e_closure[])
{
	for (int i = 0; i < e_closure[x].size(); i++)
		if (!find(e_closure[x][i], closure))
		{
			closure.push_back(e_closure[x][i]);
			find_e_closure(e_closure[x][i], closure, e_closure);
		}
}

int main()
{
	vector <int> stari, finale, e_closure[20], mat[20][20], stari_noi[20], mat_finala[20][20];
	int nr_stari, x, f, nr_stari_finale, stare_initiala, nr_alfabet, data, nr_tranzitii;
	int X, Y, nr = 0, nr_total = 0;
	char Z, alfabet[20];

	fin >> nr_stari;

	for (int i = 0; i < nr_stari; i++)
	{
		fin >> x;
		stari.push_back(x);
	}

	fin >> stare_initiala;
	fin >> nr_alfabet;
	int SIZE;
	for (SIZE = 0; SIZE < nr_alfabet; SIZE++)
		fin >> alfabet[SIZE];

	alfabet[SIZE] = '\0';
	fin >> nr_stari_finale;

	for (int i = 0; i < nr_stari_finale; i++)
	{
		fin >> f;
		finale.push_back(f);
	}
	fin >> nr_tranzitii;
	for (int i = 0; i < nr_stari; i++)
		e_closure[i].push_back(i);

	for (int i = 0; i < nr_tranzitii; i++)
		fin >> X >> Z >> Y;
		if (Z == '.')
			e_closure[X].push_back(Y);
		else
			mat[X][pozitie(Z, alfabet)].push_back(Y);
	
	for (int i = 0; i < nr_stari; i++)
		for (int j = 1; j < e_closure[i].size(); j++)
			find_e_closure(e_closure[i][j], e_closure[i], e_closure);

	for (int i = 0; i < e_closure[stare_initiala].size(); i++)
		stari_noi[0].push_back(e_closure[stare_initiala][i]);

	nr_total++;
	while (nr < nr_total)
	{
		for (int i = 0; i < nr_alfabet; i++)
		{
			for (int j = 0; j < stari_noi[nr].size(); j++)
				for (int k = 0; k < mat[stari_noi[nr][j]][i].size(); k++)
					for (int l = 0; l < e_closure[mat[stari_noi[nr][j]][i][k]].size(); l++)
						mat_finala[nr][i].push_back(e_closure[mat[stari_noi[nr][j]][i][k]][l]);
			if (mat_finala[nr][i].empty())
				continue;
			bool verif = 0;
			for (int m = 0; m < nr_total; m++)
				if (same_or_not(stari_noi[m], mat_finala[nr][i]))
				{
					verif = 1;
					break;
				}
			if (!verif)
			{
				for (int n = 0; n < mat_finala[nr][i].size(); n++)
					stari_noi[nr_total].push_back(mat_finala[nr][i][n]);
				nr_total++;
			}
		}
		nr++;
	}
	cout << "Starea initiala : A\nStari finale : ";

	for (int i = 0; i < nr_stari_finale; i++)
		for (int j = 0; j < nr_total; j++)
			for (int k = 0; k < stari_noi[j].size(); k++)
				if (stari_noi[j][k] == finale[i])
				{
					cout << char(65 + j) << ' ';
					break;
				}

	cout << endl << endl;
	for (int i = 0; i < nr_total; i++)
	{
		for (int j = 0; j < nr_alfabet; j++)
			cout << "Starea " << char(65 + i) << "(" << alfabet[j] << ")=> " << char(65 + ind_stari_finale(stari_noi, mat_finala[i][j], nr_total)) << endl;
		cout << endl;
	}

	for (int i = 0; i < nr_total; i++)
	{
		cout << "\nStarea " << char(65 + i) << " = {";
		for (int j = 0; j < stari_noi[i].size(); j++)
			if (j == stari_noi[i].size() - 1)
				cout << stari_noi[i][j] << "}";
			else
				cout << stari_noi[i][j] << ", ";
	}
	cout << endl;
	system("pause");
}
#endif
