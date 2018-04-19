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
			QuickSort(arr, left, teiler);
			QuickSort(arr, teiler + 1, right);
		}
	}

	//************
	// MergeSort *
	//************
	void MergeSort(vector<int> &a, vector<int> &b, int low, int high)
	{
		//TODO: MergeSort
	}

	//************
	// Heapsort  *
	//************

	void HeapSort(vector<int> &a, int n)
	{
		//TODO: HeapSort
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
}
