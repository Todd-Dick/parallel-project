#!/bin/bash

echo "timing for omp 1 thread\n" > omp.txt
./omp1 1 >> omp.txt
echo "timing for omp 2 thread\n" >> omp.txt
./omp1 2 >> omp.txt
echo "timing for omp 3 thread\n" >> omp.txt
./omp1 3 >> omp.txt
echo "timing for omp 4 thread\n" >> omp.txt
./omp1 4 >> omp.txt
echo "timing for omp 5 thread\n" >> omp.txt
./omp1 5 >> omp.txt
echo "timing for omp 6 thread\n" >> omp.txt
./omp1 6 >> omp.txt
echo "timing for omp 7 thread\n" >> omp.txt
./omp1 7 >> omp.txt
echo "timing for omp 8 thread\n" >> omp.txt
./omp1 8 >> omp.txt
echo "timing for omp 9 thread\n" >> omp.txt
./omp1 9 >> omp.txt
echo "timing for omp 10 thread\n" >> omp.txt
./omp1 10 >> omp.txt

