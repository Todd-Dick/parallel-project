#!/bin/bash

echo "timing for pth 1 thread\n" > pth.txt
./pth 1 >> pth.txt
echo "timing for pth 2 thread\n" >> pth.txt
./pth 2 >> pth.txt
echo "timing for pth 3 thread\n" >> pth.txt
./pth 3 >> pth.txt
echo "timing for pth 4 thread\n" >> pth.txt
./pth 4 >> pth.txt
echo "timing for pth 5 thread\n" >> pth.txt
./pth 5 >> pth.txt
echo "timing for pth 6 thread\n" >> pth.txt
./pth 6 >> pth.txt
echo "timing for pth 7 thread\n" >> pth.txt
./pth 7 >> pth.txt
echo "timing for pth 8 thread\n" >> pth.txt
./pth 8 >> pth.txt
echo "timing for pth 9 thread\n" >> pth.txt
./pth 9 >> pth.txt
echo "timing for pth 10 thread\n" >> pth.txt
./pth 10 >> pth.txt

