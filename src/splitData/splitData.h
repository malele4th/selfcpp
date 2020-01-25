/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : splitData.h
 *   author   : malele@360.cn
 *   date     : 2020-01-08
 *   info     : 
 * ======================================================== */

#ifndef _SPLITDATA_H
#define _SPLITDATA_H

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<math.h>
using namespace std;

template <class T>
void split_map_data(const T& map_data, int batch_num, vector<T>& result){
    int data_num   = map_data.size();
    int batch_size = ceil(float(data_num) / batch_num); 

    typename T::const_iterator it;
    T map_one;
    for(it = map_data.begin(); it != map_data.end(); it++){
        if(map_one.size() >= batch_size){
            result.push_back(map_one);        
            map_one.clear();
            map_one[it->first] = it->second;
        }
        else{
            map_one[it->first] = it->second;
        }
    }
    result.push_back(map_one);
}

#endif //SPLITDATA_H


