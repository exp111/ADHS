reset
set term pdf
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left

set out 'sorting_algorithm_results.pdf'
set xrange [1000:1000000]
plot \
"heapsort.txt" with linespoints title 'Heapsort',\
"quicksort.txt" with linespoints title 'Quicksort',\
"mergesort.txt" with linespoints title 'Mergesort',\
"shellsort.txt" with linespoints title 'Shellsort',\

pause -1

set out 'matrix_multiplication_results.pdf'
set xrange [1:1800]
plot \
"matrixmulcol_single.txt" with linespoints title 'matrixmul\_colmajor\_singlethread',\
"matrixmulrow_single.txt" with linespoints title 'matrixmul\_rowmajor\_singlethread',\
"matrixmulcol_max.txt" with linespoints title 'matrixmul\_colmajor\_maxthreads',\
"matrixmulrow_max.txt" with linespoints title 'matrixmul\_rowmajor\_maxthreads',\