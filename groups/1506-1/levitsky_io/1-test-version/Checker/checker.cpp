#define _CRT_SECURE_NO_WARNINGS
#include"cstdio"
#include "iostream"
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	int size;
	char* name = argv[1];
	char* answ = argv[2];

	freopen(name, "rb", stdin);
	fread(&size, sizeof(size), 1, stdin);

	int* sorted = new int[size];
	fread(sorted, sizeof(sorted), size, stdin);
	fclose(stdin);

	sort(sorted, sorted + size);
	for (int i = 0; i < size; i++)
		cout << sorted[i] << " ";
	freopen(answ, "wb", stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(sorted, sizeof(sorted), size, stdout);
	fclose(stdout);
	//fwrite(mas, sizeof(*mas), size, stdout);
}