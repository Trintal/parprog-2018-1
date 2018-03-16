#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

void main(int argc, char* argv[])
{
	int size;
	int* mas;
	char* name = argv[1];
	ifstream fin("input.txt");
	fin >> size;

	mas = new int[size];

	for (int i = 0; i < size; i++)
	{
		fin >> mas[i];
	}
	fin.close();

	freopen(name, "wb", stdout);

	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(mas, sizeof(*mas), size, stdout);

}