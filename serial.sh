#!/bin/bash
# Note: for batch run_script queue on jetson
# after correctness has been verified remove
# matrix data output in program but output data size 
#and measured run time from the rank 0 process
# then compile on jetson using
# g++ tsp_serial.cpp -o ttour -O3 -lm
# make sure this script has execute rights
#   chmod 744 ttour.sh
# Then run this batch script using
#   run_script ttour.sh
# where you specify 1 as the number of nodes
#output will be captured in ttour.txt file
echo "timing for serial" > serial.txt
./serial >> serial.txt
./serial >> serial.txt
./serial >> serial.txt
./serial >> serial.txt
./serial >> serial.txt

