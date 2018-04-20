#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <vector>
#include <omp.h>
#include "MyAlgorithms.h"

using namespace std;

int main(int argc, char** argv) {

	//***************
	// file streams *
	//***************
	ofstream textFile;

#ifdef _MERGESORT
	textFile.open("mergeSort.txt", ios::out);
#elif _HEAPSORT
	textFile.open("heapSort.txt", ios::out);
#else
	textFile.open("quickSort.txt", ios::out);
#endif


	//******************** 
	//benchmark settings *
	//********************

	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 100000;
	int numThreads = 4; //only for matrix multiplication

	//********************************************************************
	//data structures for sorting algorithms (int) and matrices (double) *
	//********************************************************************

	vector<int> array, temp_array;
	vector<double> A, B, C;

	//********************************************************************
	//Test If Algorithm works
	//********************************************************************
#ifdef _DEBUG
	MyAlgorithms::randomizeArray(array, 25);
	for (int i = 0; i < 25; i++)
	{
		std::cout << array[i] << ",";
	}
	std::cout << endl;

#ifdef _MERGESORT
	int mid = array.size() / 2;
	temp_array = vector<int>(array.begin() + mid + 1, array.end()); //Second Part of the Array
	array = vector<int>(array.begin(), array.begin() + mid); //First Part
	MyAlgorithms::MergeSort(array, temp_array, array.front(), temp_array.back());
#elif _HEAPSORT
	MyAlgorithms::HeapSort(array, array.size() - 1);
#else
	MyAlgorithms::QuickSort(array, 0, array.size() - 1);
#endif

	for (int i = 0; i < 25; i++)
	{
		std::cout << array[i] << ",";
	}
	std::cout << endl << "IsSorted: " << MyAlgorithms::isSorted(array) << endl;
	std::system("PAUSE");
#endif

	//********************************************************
	//benchmark main loop (run only ONE algorithm at a time) *
	//********************************************************

	for (int n = n_start; n < n_end; n += n_step) {
		cout << "n: " << n << endl;

		//***************************************
		//init data structure with random values*
		//***************************************

		//sorting algorithms
		MyAlgorithms::randomizeArray(array, n);

		//matrix multiplication
		//if (n>800) { n_step=11; }
		//MyAlgorithms::randomizeMatrix(A,n);
		//MyAlgorithms::randomizeMatrix(B,n);
		//C.resize(n*n);

		//****************
		//  start clock  *
		//**************** 
		dtime = omp_get_wtime();

		//**********************
		//  execute algorithm  *
		//**********************
#ifdef _MERGESORT
		//Create new array
		int mid = array.size() / 2;
		temp_array = vector<int>(array.begin() + mid + 1, array.end()); //Second Part of the Array
		array = vector<int>(array.begin(), array.begin() + mid); //First Part
		MyAlgorithms::MergeSort(array, temp_array, array.front(), temp_array.back());
#elif _HEAPSORT
		MyAlgorithms::HeapSort(array, array.size() - 1);
#else
		MyAlgorithms::QuickSort(array, 0, array.size() - 1);
#endif

		//***************
		//  stop clock  *
		//***************
		dtime = omp_get_wtime() - dtime;

		//*************************
		//  write results to file *
		//*************************
		textFile << n << "\t" << setprecision(10) << scientific << dtime << endl;

	}

	//**********************
	//  close file handles *
	//**********************

	textFile.close();
}
