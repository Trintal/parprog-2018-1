#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

int* TXTtoBIN(int& size)
{
	ifstream fin("input.txt");
	fin >> size;

	int* mas = new int[size];

	for (int i = 0; i < size; i++)
	{
		fin >> mas[i];
	}
	fin.close();

	freopen("matr.in", "wb", stdout);

	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(mas, sizeof(*mas), size, stdout);

	return mas;
}