#define _CRT_SECURE_NO_WARNINGS
#pragma once;
#include <cstdio>
#include <random>
#include <omp.h>

using namespace std;

int main(int argc, char * argv[])
{
	int size;
	int num_threads = 1;
	if (argc > 1)
	{
		num_threads = atoi(argv[1]);
		size = atoi(argv[1]);
	}
	size = atoi(argv[1]);

	int* mas = new int[size];
	int* sortedmas = new int[size];

	freopen("Sort.in", "rb", stdin);
	freopen("Sort.out", "wb", stdout);

	omp_set_num_threads(num_threads);

	fread(mas, sizeof(mas), size, stdin);

	double time = omp_get_wtime();
	//Start(size, mas, sortedmas);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(sortedmas, sizeof(sortedmas), size, stdout);

	system("pause");
	return 0;
}