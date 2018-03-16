#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	int size;
	int* sortedmas;
	char* name = argv[1];
	freopen(name, "rb", stdin);
	fread(&size, sizeof(size), 1, stdin);

	sortedmas = new int[size];

	fread(sortedmas, sizeof(*sortedmas), size, stdin);

	ofstream fout("output.txt");
	fout << size << endl;
	for (int i = 0; i < size; i++)
		fout << sortedmas[i] << " ";
	fout.close();
	return 0;
}