#ifndef _MYALGORITHMS_H_
#define _MYALGORITHMS_H_

#include <vector>
#include <iostream>

using namespace std;

namespace MyAlgorithms {
  
  //************
  // QuickSort *
  //************
  void QuickSort(vector<int> &arr, int left, int right);

  //************
  // MergeSort *
  //************
  void MergeSort(vector<int> &a, vector<int> &b, int low, int high);

  //************
  // Heapsort  *
  //************
  void HeapSort(vector<int> &a, int n);

  //************
  // Shellsort *
  //************
  void ShellSort(vector<int> &a, int n);

 
  //************************************
  //Matrix Multiplikation Column Major *
  //************************************

  void MatrixMul_ColMajor(vector<double> &A, 
			  vector<double> &B, 
			  vector<double> &C, 
			  int n, 
			  int numThreads);

  //*********************************
  //Matrix Multiplikation Row Major *
  //*********************************

  void MatrixMul_RowMajor(vector<double> &A, 
			  vector<double> &B, 
			  vector<double> &C, 
			  int n,
			  int numThreads);

  //********************
  // helper functions  *
  //********************

  double fRand(double fMin, double fMax);
  void randomizeMatrix(vector<double> &matrix, int n);   //fills vector<double> with n*n random double values
  void randomizeArray(vector<int> &array, int n);   //fills vector<int> with n random integer values
  bool isSorted(vector<int> array);
  void iterSwap(vector<int> &array, int i1, int i2);
}
#endif 
