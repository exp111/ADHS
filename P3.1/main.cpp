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
  ofstream quicksort;

  quicksort.open("quicksort.txt", ios::out | ios::app);

  
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
 
  vector<int> array,temp_array;
  vector<double> A,B,C; 


  //********************************************************
  //benchmark main loop (run only ONE algorithm at a time) *
  //********************************************************

  for (int n = n_start; n<n_end; n+=n_step) {    
    cout << "n: " << n << endl;

    //***************************************
    //init data structure with random values*
    //***************************************
    
    //sorting algorithms
    MyAlgorithms::randomizeArray(array,n);
	
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
    MyAlgorithms::QuickSort(array,0,array.size()-1);
 
   	
    //***************
    //  stop clock  *
    //***************
    dtime = omp_get_wtime() - dtime;    
    
    //*************************
    //  write results to file *
    //*************************
    quicksort << n << "\t" << setprecision(10) << scientific << dtime << endl;
    
  } 

  //**********************
  //  close file handles *
  //**********************
  
  quicksort.close();
}
