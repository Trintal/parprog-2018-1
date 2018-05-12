#define _CRT_SECURE_NO_WARNINGS
#pragma once;
#include <cstdio>
#include <random>
#include <chrono>
#include "iostream"
#include <string>
#include <ctime>
#include <queue>
#include <omp.h>


using namespace std;


union BinaryInt
{
	int d;
	unsigned char c[sizeof(double)];

	BinaryInt()
	{
		d = 0;
	}
	BinaryInt(int doub)
	{
		d = doub;
	}
};


void initData(BinaryInt *&dataArray, int size, int* mas)
{
	dataArray = new BinaryInt[size];
	for (int i = 0; i < size; i++)
	{
		dataArray[i] = BinaryInt(mas[i]);
	}
}


void RadixSort(queue<BinaryInt> &data, queue<BinaryInt> &sortedData, int numOfByte, int numOfBitInByte)
{
	queue<BinaryInt> queueZero;
	queue<BinaryInt> queueOne;
	queue<BinaryInt> MqueueZero;
	queue<BinaryInt> MqueueOne;

			if (numOfByte != -1)
			{
				while (data.size() != 0)
				{
					if (data.front().d < 0)
					{
						if (!(numOfBitInByte & data.front().c[numOfByte]))
						{
							MqueueOne.push(data.front());
							data.pop();
						}
						else
						{
							MqueueZero.push(data.front());
							data.pop();
						}
					}
					else
					{
						if (!(numOfBitInByte & data.front().c[numOfByte]))
						{
							queueZero.push(data.front());
							data.pop();
						}
						else
						{
							queueOne.push(data.front());
							data.pop();
						}
					}
				}
			}
			// recursive call must be outside of while loop above
			numOfByte = numOfBitInByte == 1 ? --numOfByte : numOfByte;
			numOfBitInByte = numOfBitInByte == 1 ? numOfBitInByte = 128 : numOfBitInByte = numOfBitInByte / 2;
			int numOfByteCopy2 = numOfByte;
			int numOfBitInByteCopy2 = numOfBitInByte;
			if (MqueueOne.size() > 1)
				RadixSort(MqueueOne, sortedData, numOfByteCopy2, numOfBitInByteCopy2);
			//#pragma omp section
			while (MqueueOne.size() != 0)
			{
				sortedData.push(MqueueOne.front());
				MqueueOne.pop();
			}

			if (MqueueZero.size() > 1)
				RadixSort(MqueueZero, sortedData, numOfByte, numOfBitInByte);

			//#pragma omp section

			while (MqueueZero.size() != 0)
			{
				sortedData.push(MqueueZero.front());
				MqueueZero.pop();
			}
			//////////////

			if (queueZero.size() > 1)
				RadixSort(queueZero, sortedData, numOfByte, numOfBitInByte);
			//#pragma omp section

			while (queueZero.size() != 0)
			{
				sortedData.push(queueZero.front());
				queueZero.pop();
			}

			if (queueOne.size() > 1)
				RadixSort(queueOne, sortedData, numOfByteCopy2, numOfBitInByteCopy2);
			//#pragma omp section

			while (queueOne.size() != 0)
			{
				sortedData.push(queueOne.front());
				queueOne.pop();
			}
}


void setResult(queue<BinaryInt> sortedData, BinaryInt *data)
{
	//int count = sortedData.size() * omp_get_thread_num();
	int left = sortedData.size()* omp_get_thread_num();
	int right = sortedData.size()* (omp_get_thread_num()+1);
	for (left; left < right; left++)
	{
		data[left] = sortedData.front();
		sortedData.pop();
	}
}

void merge(int* Sorted, BinaryInt *Array, int size)
{
		int left = size * omp_get_thread_num();
		int right = size * (omp_get_thread_num() + 1);
		int leftsize = left +size;
		int rightsize = right + size;
		int index = 0;

		while ((left < leftsize) && (right<rightsize))
		{
			int elemfirst = Array[left].d;
			int elemsecond = Array[right].d;

			if (Array[left].d < Array[right].d)
			{
				Sorted[index] = elemfirst;
				left++;
				//tmp = Array[left].d;
				//Array[left].d = Array[right].d;
				//Array[right].d = tmp;
				//right++;
			}
			else
			{
				Sorted[index] = elemsecond;
				right++;
			}
		}

		while (left < leftsize)
		{
			Sorted[index] = Array[left].d;
			left++;
			index++;
		}
		while (right < rightsize)
		{
			Sorted[index] = Array[right].d;
			right++;
			index++;
		}
}

int main(int argc, char * argv[])
{
	int size;
	char* input = "ExArr.in";
	char* output = "SortedExArr.out";
	int thread = 4;

	if (argc > 3)
	{
		thread = atoi(argv[1]);
		input = argv[2];
		output = argv[3];
	}

	omp_set_num_threads(thread);

	freopen(input, "rb", stdin);
	fread(&size, sizeof(int), 1, stdin);
	int* mas = new int[size];
	int* sorted = new int[size];
	fread(mas, sizeof(int), size, stdin);
	fclose(stdin);

	//BinaryInt *nonParallel = nullptr;
	BinaryInt *parallel = new BinaryInt[size];
	//BinaryInt *parallelCopy = new BinaryInt[size];
	double startTime = 0;
	double endTime = 0;
	double timeOfNonParallel = 0;

	queue<BinaryInt> queueData;
	queue<BinaryInt> sortedData;

	startTime = clock();

	initData(parallel, size, mas);

	int piece = size / thread;
	int n = 0;
	/////////////////////////////////
#pragma omp parallel private (queueData, sortedData)
	{
		startTime = clock();
#pragma omp for
		for (int i = 0; i < size; i++) {
			queueData.push(parallel[i]);
		}

		int u = 3; int o = 128;
		RadixSort(queueData, sortedData, u, o);

		setResult(sortedData, parallel);

#pragma omp barrier

#pragma omp master
		{
			for (n = 0; n < size; n++)
			{
				cout << parallel[n].d << " ";
			}
			cout << endl << endl;
		}

		int pairs = thread / 2;
		int pairsprev = thread / 2;
		int offset = 2;

		int counter = 2;
		int sendsize = piece;
		/*while (pairs > 1)
		{
			pairs = pairs / 2 + pairs % 2;
			if (pairsprev % pairs == 0 || omp_get_thread_num() != (pairs - 1) * offset)
			{
				int sendsize = piece;
				cout << "Ama proces :" << omp_get_thread_num() << endl;
				merge(sorted, parallel, sendsize);
				sendsize *= 2;
			}
			pairsprev = pairs;
			offset *= 2;
		}*/

		while (pairs > 1)
		{
			pairs = pairs / 2 + pairs % 2;
			if(omp_get_thread_num() % counter == 0 || omp_get_thread_num() % counter == counter)
				merge(sorted, parallel, sendsize);
			sendsize *= 2;
			counter *= 2;
		}

//#pragma omp for
//		for (int i = 0; i < piece; i++)
//		{
//			sorted[i] = parallel[i].d;
//		}
	}

#pragma omp master
	{
		for (n = 0; n < size; n++)
		{
			cout << sorted[n] << " ";
		}
		cout << endl << endl;
	}


	cout << endl << endl;
	endTime = clock();
	timeOfNonParallel = endTime - startTime;
	cout << "---" << timeOfNonParallel << "---" << endl;


	freopen(output, "wb", stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(sorted, sizeof(*sorted), size, stdout);
	fclose(stdout);

	delete[] mas;
	delete[] sorted;
	//delete[] nonParallel;
	delete[] parallel;
	//delete[] parallelCopy;

	return 0;
}