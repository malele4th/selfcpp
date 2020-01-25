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

#include "readFile.h"
#include "splitString.h"

//#include <boost/thread/thread.hpp>
//#include <boost/bind.hpp>

using namespace std;

template<class T>
class Kmeans{
    public:
        Kmeans();
        ~Kmeans();
        void print(T a);
   
    
    private:
        vector<vector<T> > dataSet;
        vector<string> keyLabel;
    
};



#endif //KMEANS_H





