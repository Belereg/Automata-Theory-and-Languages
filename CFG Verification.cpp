#include "libraries.h"

struct NonTerminal
{
	int production_number;
	char non_terminal, productions[20][200];
};

struct Node
{
	char str[200];
	Node* son[100];
};

int NT_number;
bool OK;
NonTerminal NT[50];

bool check(Node* root, char checked_word[])
{
	if (strcmp(root->str, checked_word) == 0 || OK || (strlen(root->str) == 0 && strcmp(checked_word, ".") == 0))
	{
		OK = true;
		return true;
	}

	int count = 0, count_Non_Terminals = 0;

	for (int i = 0; i < strlen(root->str); i++)
		if (root->str[i] >= 'a' && root->str[i] <= 'z')
			count++;

	for (int i = 0; i < strlen(root->str); i++)
		if (root->str[i] >= 'A' && root->str[i] <= 'Z')
			count_Non_Terminals++;

	if (count > strlen(checked_word) || count_Non_Terminals > 7)
		return false;

	for (int i = 0; i < strlen(root->str) && !OK; i++)
		if (root->str[i] >= 'A' && root->str[i] <= 'Z')
			for (int j = 0; j < NT_number && !OK; j++)
				if (NT[j].non_terminal == root->str[i])
					for (int z = 0; z < NT[j].production_number && !OK; z++)
					{
						root->son[z] = new Node;

						strcpy(root->son[z]->str, root->str);

						char aux[200];
						strcpy(aux, root->son[z]->str + i + 1);

						if (NT[j].productions[z][0] == '.')
						{
							strcpy(root->son[z]->str + i, aux);
						}
						else
						{
							strcpy(root->son[z]->str + i, NT[j].productions[z]);
							strcpy(root->son[z]->str + strlen(root->son[z]->str), aux);
						}
						check(root->son[z], checked_word);
					}

	if (OK)
		return true;
	return false;
}

int main()
{
	ifstream fin("gic.in");
	char startPoint;

	fin >> NT_number >> startPoint;

	for (int i = 0; i < NT_number; i++)
	{
		fin >> NT[i].non_terminal >> NT[i].production_number;

		for (int j = 0; j < NT[i].production_number; j++)
			fin >> NT[i].productions[j];

	}
	Node* ROOT = new Node;

	ROOT->str[0] = startPoint;
	ROOT->str[1] = '\0';

	char checked_word[200], choice;
	do
	{
		OK = false;
		cout << "Type the word you want to verify: ";
		cin >> checked_word;

		if (check(ROOT, checked_word))
			cout << "Word accepted.";
		else
			cout << "Word denied.";

		cout << "\n\nDo you want to verify another word? (Y / N) ";
		cin >> choice;
		cout << endl;
	} while (choice == 'y' || choice == 'Y');

	system("pause");
}
