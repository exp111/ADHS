#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <omp.h>
#include "MyAlgorithms.h"

using namespace std;

enum CHOICES
{
	QUICKSORT = 1,
	HEAPSORT = 2,
	MERGESORT,
	SHELLSORT
};

int main(int argc, char** argv) {


	cout << "Choose the algorithm:" << endl
		<< "1) Quick Sort" << endl
		<< "2) Heap Sort" << endl
		<< "3) Merge Sort" << endl
		<< "4) Shell Sort" << endl
		<< "9) All" << endl
		<< "? > ";

	int choice = 0;
	cin >> choice;

	//******************** 
	//benchmark settings *
	//********************

	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 100000;
	int numThreads = 4; //only for matrix multiplication

	//********************
	//* Set Window Title *
	//********************
	string titleCommand = "title Current Algorithm: ";

	switch (choice)
	{
	case QUICKSORT:
		titleCommand += "Quick Sort";
		break;
	case HEAPSORT:
		titleCommand += "Heap Sort";
		break;
	case MERGESORT:
		titleCommand += "Merge Sort";
		break;
	case SHELLSORT:
		titleCommand += "Shell Sort";
		break;
	default:
		break;
	}

	titleCommand += ". N (start, step, end): " + to_string(n_start) + 
					", " + to_string(n_step) + 
					", " + to_string(n_end) + ".";
	system(titleCommand.c_str());

	//********************************************************************
	//data structures for sorting algorithms (int) and matrices (double) *
	//********************************************************************

	vector<int> array, temp_array;
	vector<double> A, B, C;

	//********************************************************************
	//Test If Algorithm works
	//********************************************************************
#ifdef _DEBUG
	int testInt = 25;
	MyAlgorithms::randomizeArray(array, testInt);
	
	for (int i = 0; i < testInt; i++)
	{
		std::cout << array[i] << ",";
	}
	std::cout << endl;

	switch (choice)
	{
	case QUICKSORT:
	{
		MyAlgorithms::QuickSort(array, 0, (int)array.size() - 1);
		break;
	}
	case HEAPSORT:
		MyAlgorithms::HeapSort(array, (int)array.size() - 1);
		break;
	case MERGESORT:
	{
		temp_array = vector<int>(array.size()); //Second Part of the Array
		MyAlgorithms::MergeSort(array, temp_array, 0, (int)array.size() - 1);
		break;
	}
	case SHELLSORT:
		MyAlgorithms::ShellSort(array, (int)array.size());
		break;
	default:
		break;
	}

	for (int i = 0; i < testInt; i++)
	{
		std::cout << array[i] << ",";
	}
	std::cout << endl << "IsSorted: " << MyAlgorithms::isSorted(array) << endl;
	std::system("PAUSE");
#endif

	//***************
	// file streams *
	//***************
	ofstream textFile;
	string fileName;

	switch (choice)
	{
	case QUICKSORT:
		fileName = "quicksort.txt";
		break;
	case HEAPSORT:
		fileName = "heapsort.txt";
		break;
	case MERGESORT:
		fileName = "mergesort.txt";
		break;
	case SHELLSORT:
		fileName = "shellsort.txt";
		break;
	default:
		cout << "Not a valid choice. Frick off." << endl;
		exit(1);
		break;
	}
	textFile.open(fileName, ios::out);

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
		switch (choice)
		{
		case QUICKSORT:
		{
			MyAlgorithms::QuickSort(array, 0, (int)array.size() - 1);
			break;
		}
		case HEAPSORT:
		{
			MyAlgorithms::HeapSort(array, (int)array.size() - 1);
			break;
		}
		case MERGESORT:
		{
			temp_array = vector<int>(array.size()); //Second Part of the Array
			MyAlgorithms::MergeSort(array, temp_array, 0, (int)array.size() - 1);
			break;
		}
		case SHELLSORT:
			MyAlgorithms::ShellSort(array, (int)array.size());
			break;
		default:
			break;
		}

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
