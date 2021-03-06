/* ========================================================
 *   Copyright (C) 2019 All rights reserved.
 *   
 *   filename : main.cpp
 *   author   : malele@360.cn
 *   date     : 2019-12-31
 *   info     : 
 * ======================================================== */

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<ctime>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "readFile.h"
#include "splitString.h"
#include "similarity.h"
#include "splitData.h"
#include "scaler.h"

using namespace std;

int main(int argc, char *argv[]){
    time_t start_time = time(0);
    cout<< "=== start time === " << ctime(&start_time) <<endl;
    const char *input_file  = "data/itag_embedding";

    vector<vector<float> > data_set;
    vector<string> data_label;
    ReadFile read_file;
    read_file.read_file_vec_vec(input_file, data_label, data_set);
    
    //ScalerMinMax scaler_obj;
    ScalerStandard scaler_obj;
    vector<vector<float> > scaler_data_set;
    scaler_obj.fit(data_set, scaler_data_set);
    
    for(int i = 0; i < scaler_data_set.size(); i++){
        cout<<endl;
        cout<<"dim = "<< scaler_data_set[i].size() <<endl;
        for(int j = 0; j < scaler_data_set[i].size(); j++){
            cout<< scaler_data_set[i][j] << endl;
        }   
    }   

    return 0;
}

