//
//  read_pth.cpp
//  412project
//
//  Created by Todd Dick on 12/16.
//  Copyright © 2016 Todd Dick. All rights reserved.
//

/* This program will read in 10 .png files and write the data byte by byte to separate vector data type containers to be used for whatever purposes. This program is designed to be a baseline program to measure the time it takes to read in 10 media files. This program can be extended to do something with the vectors, but that is outside of the scope of this project.*/
/* There is no way to dynamically name vectors in C or C++, so this program will only use 10 files. To use more, more vectors need to be declared.*/
/* Prior to using this program, enter the following from command line in the directory containing your 10 media files. "ls *.<filetype> > list.txt" without the quotes.*/
/* to compile --- g++ read_pth.cpp -o pth -O3 -std=c++11 -pthread*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/time.h>
#include <pthread.h>

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
vector<string> globalList;

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
void MakeVector(int number){
    FILE * infile;
    string tempStr = globalList[number];
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

void *ThreadFunc(void *arg){
    int *start_end = (int *) arg;
    int start = start_end[0];
    int end = start_end[1];
    for(int i = start; i < end; i++){
        MakeVector(i);
    }
    return arg;
}

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        cout << "Usage : ./pth <threadcount> ." << endl;
        exit(1);
    }
    vector<string> list;
    int i;
    MakeList(list);
    globalList = list;
    
    int thread_count = stoi(argv[1]);
    TIMER_CLEAR;
    TIMER_START;
    int tid;
    pthread_t threads[thread_count];
    int start_end[thread_count][2];
    int errcode;
    int startVal = 0, endVal;
    int groupMod = 10 % thread_count;
    for (tid = 0; tid < thread_count; tid++){
        start_end[tid][0] = startVal;
        int groupSize = 10/thread_count;
        if (tid < groupMod){
            groupSize++;
        }
        start_end[tid][1] = startVal+groupSize;
        startVal += groupSize;
        errcode = pthread_create(&threads[tid], NULL, ThreadFunc,&start_end[tid]);
        if (errcode) {
            cerr << "Pthread creation Error: " << strerror(errcode) << endl;
            exit(1);
        }
    }
    for ( tid = 0; tid < thread_count; tid++) {
        errcode = pthread_join(threads[tid], NULL);
    }
    if (errcode) {
        cerr << "Pthread join Error: " << strerror(errcode) << endl;
        exit(1);
    }
    
    TIMER_STOP;
    cout << "Execution time = " << TIMER_ELAPSED/1000000.0 << endl;
    
    //Do something with the vectors...
    return 0;
}
