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
	SHELLSORT,
	MATRIX_MUL_ROW,
	MATRIX_MUL_COL
};

int main(int argc, char** argv) {

	cout << "Choose the algorithm:" << endl
		<< "1) Quick Sort" << endl
		<< "2) Heap Sort" << endl
		<< "3) Merge Sort" << endl
		<< "4) Shell Sort" << endl
		<< "5) Matrix Mul Row Major" << endl
		<< "6) Matrix Mul Col Major" << endl
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
	int n_end = 1000000;
	int numThreads = 4; //only for matrix multiplication

	switch (choice)
	{
	case MATRIX_MUL_ROW:
	case MATRIX_MUL_COL:
		cout << "n Start: ? ";
		cin >> n_start;
		cout << "n Step: ? ";
		cin >> n_step;
		cout << "n End: ? ";
		cin >> n_end;
		cout << "num Threads: ? ";
		cin >> numThreads;
		break;
	default:
		break;
	}

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
	case MATRIX_MUL_ROW:
		titleCommand += "MatrixMulRowMajor";
		break;
	case MATRIX_MUL_COL:
		titleCommand += "MatrixMulColMajor";
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
	switch (choice)
	{
	default:
	{
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
		break;
	}
	case MATRIX_MUL_ROW:
	{
		A.push_back(1);
		A.push_back(2);
		A.push_back(3);
		A.push_back(4);
		B.push_back(5);
		B.push_back(6);
		B.push_back(7);
		B.push_back(8);
		C.resize(4);
		MyAlgorithms::MatrixMul_RowMajor(A, B, C, 2, 1);
		break;
	}
	case MATRIX_MUL_COL:
	{
		A.push_back(1);
		A.push_back(3);
		A.push_back(2);
		A.push_back(4);
		B.push_back(5);
		B.push_back(7);
		B.push_back(6);
		B.push_back(8);
		C.resize(4);
		MyAlgorithms::MatrixMul_ColMajor(A, B, C, 2, 1);
		break;
	}
	}
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
	case MATRIX_MUL_ROW:
		fileName = "matrixmulrow.txt";
		break;
	case MATRIX_MUL_COL:
		fileName = "matrixmulcol.txt";
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

		switch (choice)
		{
		default:
			//sorting algorithms
			MyAlgorithms::randomizeArray(array, n);
			temp_array = vector<int>(n); //Empty Temp Array
			break;
		case MATRIX_MUL_ROW:
		case MATRIX_MUL_COL:
			//matrix multiplication
			if (n > 800)
				n_step = 11;
			MyAlgorithms::randomizeMatrix(A, n);
			MyAlgorithms::randomizeMatrix(B, n);
			C.resize(n*n);
			break;
		}

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
			MyAlgorithms::QuickSort(array, 0, (int)array.size() - 1);
			break;
		case HEAPSORT:
			MyAlgorithms::HeapSort(array, (int)array.size() - 1);
			break;
		case MERGESORT:
			MyAlgorithms::MergeSort(array, temp_array, 0, (int)array.size() - 1);
			break;
		case SHELLSORT:
			MyAlgorithms::ShellSort(array, (int)array.size());
			break;
		case MATRIX_MUL_ROW:
			MyAlgorithms::MatrixMul_RowMajor(A, B, C, n, numThreads);
			break;
		case MATRIX_MUL_COL:
			MyAlgorithms::MatrixMul_ColMajor(A, B, C, n, numThreads);
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
