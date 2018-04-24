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
				iterSwap(arr, i, j);
		} while (i < j);

		if (arr[i] > arr[right])
			iterSwap(arr, i, right);//swap

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
	void merge(vector<int> &a, vector<int> &b, int low, int mid, int high)
	{
		//TODO: merge()
		int i, j, k;

		//temparray füllen
		for (i = low; i <= high; i++)
			b[i] = a[i];

		i = low; j = mid + 1; k = low;
		//check both sites(i,j) & put smaller into a[k]
		while (i <= mid && j <= high)
			if (b[i] <= b[j])
				a[k++] = b[i++];
			else
				a[k++] = b[j++];

		//falls im ersten array noch inhalt -> in a reinkopieren
		while (i <= mid)
			a[k++] = b[i++];

		//no need to check zweites array cuz it's already at the right position then
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
			merge(a, b, low, mid, high);
		}
	}

	//************
	// Heapsort  *
	//************
	void heapify(vector<int> &a, int n, int i)
	{
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int largest = i;

		//Is left child in the heap && larger?
		if (left <= n && a[left] > a[largest])
		{
			largest = left;
		}

		//Is right child in the heap && larger?
		if (right <= n && a[right] > a[largest])
		{
			largest = right;
		}

		if (largest != i) //Don't need to swap if we've the largest
		{
			//Swap the larger up
			iterSwap(a, i, largest);

			//Now check again recursive
			heapify(a, n, largest);
		}
	}

	void HeapSort(vector<int> &a, int n)
	{
		//Create Heap (weird tree like structure; we don't actually create a tree here; it's more like a mental tree)
		//The first element is the highest
		//Move the first element to the last in the heap
		//Decrease Heapsize
		//"Heapify" the array again
		//repeat till size <= 1

		int heapSize = n;

		//Make Heap
		//Start at the last child - 1; 
		//n/2 cause we split the array into two sides (left/right) and both sides have around the same amount
		////-1 cause it's useless if we start at the last cause why should we trade the last with their childs (which don't exist)
		//Then we work our way up the heap
		for (int i = n / 2; i >= 0; i--)
			heapify(a, n, i);
		
		while (heapSize > 0) //Till only one element is unsorted (well it's sorted then cuz it's the lowest)
		{
			iterSwap(a, 0, heapSize); //Swap highest (first cause heap)
			heapSize--; //So we don't swap accidentaly the last elements (the now highest)
			//Heapify again (as we now have a smaller anker node; the childs should be the largest element on the heap and should be swapped to top)
			heapify(a, heapSize, 0);
		}
	}

	//************
	// Shellsort *
	//************
	void ShellSort(vector<int> &a, int n)
	{
		//Starte bei gap = n/2
		//Starte bei i = gap und gehe davon hoch bis n
		//Vergleiche element bei j(=i) mit element bei j-gap ob kleiner und swappe wenn a[j] kleiner
		//Gap /2; wenn gap == 0 quit

		//Habard's Increament
		vector<int> gaps;
		for (int i = 1, j = 1; j < n; i++) 
		{
			gaps.push_back(j);
			j = pow(2, i) - 1; //2^k - 1
		}

		//Starte mit gap; der später verkleinert wird
		for (int s = gaps.size() - 1, gap = s >= 0 ? gaps[s] : 0; gap > 0 && s >= 0; s--, gap = s >= 0 ? gaps[s] : 0)
		{
			//Von gap hochgehen
			for (int i = gap; i < n; i++)
			{
				// A[i] zwischenspeichern
				int temp = a[i];

				// alle elemente die kleiner als a[i] und bei a[i-gap*x] sind hochschieben || direkt swappen (inefficient tho)
				int j = i;
				for (; j >= gap && a[j - gap] > temp; j -= gap)
					a[j] = a[j - gap];

				//temp nun an der richtigen stelle wieder einfügen
				a[j] = temp;
			}
		}
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

	void iterSwap(vector<int> &array, int i1, int i2)
	{
		iter_swap(array.begin() + i1, array.begin() + i2);
	}
}
