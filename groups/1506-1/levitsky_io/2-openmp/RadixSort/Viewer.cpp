#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

void BINtoTXT(int size, int* sortedmas)
{
	freopen("matr.out", "rb", stdin);

	fread(&size, sizeof(size), 1, stdin);
	fread(sortedmas, sizeof(*sortedmas), size, stdin);

	ofstream fout("output.txt");
	for (int i = 0; i < size; i++)
		fout << sortedmas[i] << endl;
	fout.close();
}