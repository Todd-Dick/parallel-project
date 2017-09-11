//
//  read_omp.cpp
//  412project
//
//  Created by Todd Dick on 12/16.
//  Copyright © 2016 Todd Dick. All rights reserved.
//

/* This program will read in 10 .png files and write the data byte by byte to separate vector data type containers to be used for whatever purposes. This program is designed to be a baseline program to measure the time it takes to read in 10 media files. This program can be extended to do something with the vectors, but that is outside of the scope of this project.*/
/* There is no way to dynamically name vectors in C or C++, so this program will only use 10 files. To use more, more vectors need to be declared.*/
/* Prior to using this program, enter the following from command line in the directory containing your 10 media files. "ls *.<filetype> > list.txt" without the quotes.*/
/* to compile --- g++ read_omp.cpp -o omp -O3 -std=c++11 -fopenmp */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

#define TIMER_CLEAR     (tv1.tv_sec = tv1.tv_usec = tv2.tv_sec = tv2.tv_usec = 0)
#define TIMER_START     gettimeofday(&tv1, (struct timezone*)0)
#define TIMER_ELAPSED   ((long long) (tv3.tv_usec)+((long long) (tv3.tv_sec)*1000000))
#define TIMER_STOP      {gettimeofday(&tv2, (struct timezone*)0);timersub(&tv2,&tv1,&tv3);}
struct timeval tv1,tv2,tv3;

vector<uint8_t> file0;
vector<uint8_t> file1;
vector<uint8_t> file2;
vector<uint8_t> file3;
vector<uint8_t> file4;
vector<uint8_t> file5;
vector<uint8_t> file6;
vector<uint8_t> file7;
vector<uint8_t> file8;
vector<uint8_t> file9;

void MakeList(vector<string> &list){
    ifstream infile;
    string line;
    
    infile.open("list.txt");
    if (!infile){
        cout << "error opening list.txt file" << endl;
        exit(1);
    }
    while(getline(infile,line)){
        list.push_back(line);
    }
    infile.close();
}

// Hybrid of C/C++ methods for reading binary, because Jetson does not support C++14 and those are the methods I originally used.
void MakeVector(int number, vector<string> &list){
    FILE * infile;
    string tempStr = list[number];
    const char* filePath = tempStr.c_str();
    infile = fopen(filePath,"rb");
    
    fseek(infile,0L,SEEK_END);
    uint64_t fileSize = ftell(infile);
    fseek(infile,0L,SEEK_SET);
    uint8_t buff[1] = {0};
    int i = 0;
    while( i < fileSize ){
        size_t readStuff = fread(&buff,1,sizeof(uint8_t),infile);
        switch(number){
            case 0:
                file0.push_back(buff[0]);
                break;
            case 1:
                file1.push_back(buff[0]);
                break;
            case 2:
                file2.push_back(buff[0]);
                break;
            case 3:
                file3.push_back(buff[0]);
                break;
            case 4:
                file4.push_back(buff[0]);
                break;
            case 5:
                file5.push_back(buff[0]);
                break;
            case 6:
                file6.push_back(buff[0]);
                break;
            case 7:
                file7.push_back(buff[0]);
                break;
            case 8:
                file8.push_back(buff[0]);
                break;
            case 9:
                file9.push_back(buff[0]);
                break;
            default:
                break;
        }
        i++;
    }
    fclose(infile);
    
    
}


int main(int argc, const char * argv[]) {
    // generic useful variable(s)
    int i;
    
    // get a list of filenames
    vector<string> list;
    MakeList(list);
    
    // set up omp

    omp_set_dynamic(0);
    
    if(argc == 1){
        cout << "Usage : ./omp <number of threads>. Try again, set number of threads." << endl;
        exit(1);
    }
    int number = stoi(argv[1]);
    if(number > 10){
        cout << "Number of threads must be < 10." << endl;
        exit(1);
    }
    else{
        omp_set_num_threads(number);
    }
    // start timer
    TIMER_CLEAR;
    TIMER_START;
#pragma omp parallel for
    for (i = 0; i < list.size(); i++){
        MakeVector(i,list);
    }
    TIMER_STOP;
    cout << "Execution time = " << TIMER_ELAPSED/1000000.0 << endl;
    
    //Do something with the vectors...
    return 0;
}
