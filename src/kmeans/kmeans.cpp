/* ========================================================
 *   Copyright (C) 2019 All rights reserved.
 *   
 *   filename : kmeans.cpp
 *   author   : malele@360.cn
 *   date     : 2020-01-09
 *   info     : 
 * ======================================================== */

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<ctime>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "kmeans.h"
#include "readFile.h"
#include "splitString.h"

using namespace std;


Kmeans::Kmeans(){
}

Kmeans::~Kmeans(){
}


void Kmeans::loadDataSet(const char *file_name){
    read_file.read_file_vec_vec(file_name, keyLabel, dataSet);
    sampleNumber = dataSet.size();
    sampleDim = dataSet[0].size();
}

void Kmeans::kmeans(int clusterNumber){
    cout << clusterNumber << endl;
}

int main(int argc, char *argv[]){
    cout<<"hello..."<<endl;
    
    const char *input_file  = "../data/itag_embedding";
    Kmeans kmeans;
    kmeans.loadDataSet(input_file); 
    kmeans.kmeans(10);

    return 0;
}



