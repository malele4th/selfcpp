/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : kmeans.h
 *   author   : malele@360.cn
 *   date     : 2020-01-09
 *   info     : 
 * ======================================================== */

#ifndef _KMEANS_H
#define _KMEANS_H

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<ctime>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "readFile.h"
#include "splitString.h"

using namespace std;

class Kmeans{
    public:
        Kmeans();
        ~Kmeans();
        void loadDataSet(const char *file_name);
        void kmeans(int clusterNumber);
    private:
        ReadFile read_file;
        vector<vector<float> > dataSet;
        vector<string> keyLabel;
        int sampleNumber;
        int sampleDim;
};

#endif //KMEANS_H


