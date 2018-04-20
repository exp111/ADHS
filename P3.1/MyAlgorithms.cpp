#include "MyAlgorithms.h"
#include <omp.h>
#include <algorithm>

namespace MyAlgorithms
{

	//************
	// QuickSort *
	//************
	int teile(vector<int> &arr, int left, int right)
	{
		int i = left;
		int j = right - 1; //Don't start with the last element cause then you wouldn't find any smaller elements cause we start at pivot
		int pivot = arr[right];

		do
		{
			while (i < right - 1 && arr[i] < pivot)//Finde Element von links das größer als pivot ist
				i++;
			while (j > left && arr[j] >= pivot)  //Finde ELement von rechts das kleiner als pivot ist
				j--; 

			if (i < j) //Tausche wenn i < j ist bzw der größere wert links ist
				iter_swap(arr.begin() + i, arr.begin() + j);
		} while (i < j);

		if (arr[i] > arr[right])
			iter_swap(arr.begin() + i, arr.begin() + right);//swap

		return i;
	}

	void QuickSort(vector<int> &arr, int left, int right)
	{
		if (left < right)
		{
			//Teile Liste in 2 Teile:
			int teiler = teile(arr, left, right);
			//Rekursiv die Teillisten sortieren
			QuickSort(arr, left, teiler); //Alle links vom teiler sollten kleiner als pivot sein
			QuickSort(arr, teiler + 1, right);
		}
	}

	//************
	// MergeSort *
	//************
	void merge(vector<int> &a, vector<int> &b, int low, int high)
	{
		vector<int> tmp;
		int i = low, j = high;
		while (i < high)
		{
			if (a.empty()) //No need to check then
			{
				tmp.push_back(b.front());
				b.erase(b.begin());
			}
			else if (b.empty()) //No need to check then
			{
				tmp.push_back(a.front());
				a.erase(a.begin());
			}
			else //Compare front elements and push smaller
			{
				if (a.front() <= b.front())
				{
					tmp.push_back(a.front());
					a.erase(a.begin());
				}
				else
				{
					tmp.push_back(b.front());
					b.erase(b.begin());
				}
			}
		}
		a = tmp;
	}

	void MergeSort(vector<int> &a, vector<int> &b, int low, int high)
	{
		//TODO: MergeSort
		//Teile Array in möglichst gleiche hälften
		//Repeat till array sizes sind == 1
		//Vergleiche vordere elemente der arrays und merge die kleinsten zuerst in ein neues array
		//Repeat till all sorted
		if (low < high)
		{
			int mid = (low + high) / 2;
			MergeSort(a, b, low, mid);
			MergeSort(a, b, mid + 1, low);

			//Merge Array
			merge(a, b, low, high);
		}
	}

	//************
	// Heapsort  *
	//************
	void heapify(vector<int> &a, int n)
	{
		//TODO: Heapify()
	}

	void HeapSort(vector<int> &a, int n)
	{
		//TODO: HeapSort
		//Create Heap (weird tree like structure)
		//The first element is the highest
		//Move the first element to the last in the heap
		//Decrease Heapsize
		//"Heapify" the array again
		//repeat till size <= 1

		int heapSize = n;
		//TODO: Is it allowed to use this make_heap?
		make_heap(a.begin(), a.end());
		
		while (heapSize > 0) //Till only one element is unsorted (well it's sorted then cuz it's the lowest)
		{
			iter_swap(a.begin(), a.begin() + heapSize); //Swap highest (first cause heap)
			heapSize--; //So we don't swap accidentaly the last elements (the now highest)
			//Heapify
			//TODO: Use heapify function; this is way2slow too
			make_heap(a.begin(), a.begin() + heapSize);
		}
	}

	//************
	// Shellsort *
	//************
	void ShellSort(vector<int> &a, int n)
	{
		//TODO: ShellSort
	}

	//************************************
	//Matrix Multiplication Column Major *
	//************************************

	void MatrixMul_ColMajor(vector<double> &A,
		vector<double> &B,
		vector<double> &C,
		int n,
		int numThreads)
	{
		//lda, ldb, ldc are leading dimensions of matrices A,B and C
		int lda = n;
		int ldb = n;
		int ldc = n;
		double s = 0.0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				s = 0.0;
				for (int k = 0; k < n; k++) {
					s = s + A[i + k*lda] * B[k + j*ldb];
				}
				C[i + j*ldc] = s;
			}
		}
	}

	//*********************************
	//Matrix Multiplication Row Major *
	//*********************************

	void MatrixMul_RowMajor(vector<double> &A,
		vector<double> &B,
		vector<double> &C,
		int n,
		int numThreads)
	{
		//TODO: MatrixMult

	}

	//********************
	// helper functions  *
	//********************
	double fRand(double fMin, double fMax) {
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}

	void randomizeMatrix(vector<double> &matrix, int n) {
		matrix.resize(n*n);
		int i;
		for (i = 0; i < matrix.size(); i++)
			matrix[i] = fRand(-1000, 1000);
	}

	void randomizeArray(vector<int> &array, int n) {
		array.resize(n);

		for (int i = 0; i < array.size(); i++)
			array[i] = rand() % 1000000;
	}
	bool isSorted(vector<int> array)
	{
		if (array.size() < 2)
			return true;
		for (int i = 1; i < array.size(); i++)
		{
			if (array[i] < array[i - 1])
				return false;
		}
		return true;
	}
}
