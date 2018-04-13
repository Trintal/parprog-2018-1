#define _CRT_SECURE_NO_WARNINGS
#include"cstdio"
#include "iostream"
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	char* name = "SortedExArr.out";
	char* answ = "ExIdealAnsw.out";


	if (argc > 2)
	{
		name = argv[1];
		answ = argv[2];
	}

	int size;
	int size2;
	bool OK = true;

	freopen(name, "rb", stdin);
	fread(&size, sizeof(int), 1, stdin);
	int* mas = new int[size];
	fread(mas, sizeof(int), size, stdin);
	fclose(stdin);

	freopen(answ, "rb", stdin);
	fread(&size2, sizeof(size2), 1, stdin);
	int* sorted = new int[size];
	fread(sorted, sizeof(int), size2, stdin);
	fclose(stdin);

	if (size != size2)
	{
		cout << "Different sizes!" << endl;
		return 0;
	}

	//sort(sorted, sorted + size);
	ofstream fout("Result.txt");
	fout << size << endl << endl;

	for (int i = 0; i < size; i++)
	{
		fout << mas[i] << " ";
		fout << sorted[i] << " | ";
		if (mas[i] != sorted[i])
		{
			fout << "Bad sorting";
			fout.close();
			break;
		}
	}
	if (OK)
	{
		fout << "All right";
		fout.close();
	}

	delete[] sorted;
	delete[] mas;
}