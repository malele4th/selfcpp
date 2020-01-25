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

using namespace std;


int main(int argc, char *argv[]){
    time_t start_time = time(0);
    cout<< "=== start time === " << ctime(&start_time) <<endl;
    const char *input_file  = "data/itag_embedding";

    ReadFile read_file;
    /*
    map<string, vector<float> > key_vec_map;
    read_file.read_file_key_emb(input_file, key_vec_map);  // get [key, vec_emb] from file

    Similarity similarity;
    map<string, vector<float> >::iterator it;
    for(it = key_vec_map.begin(); it != key_vec_map.end(); it++){
        string key = it->first;
        vector<float> emb = it->second;
        cout << key <<endl;
    }
    */
    vector<string> key_vec;
    vector<vector<float> > data_vec_vec;
    read_file.read_file_vec_vec(input_file, key_vec, data_vec_vec);

    cout<< key_vec.size() <<endl;
    cout<< data_vec_vec.size()<<endl;
    
    for(int i=0;i<data_vec_vec.size();i++){
        cout<<endl;
        for(int j=0; j < data_vec_vec[i].size(); j++){
            cout<< data_vec_vec[i][j] <<endl;
        }   
    }   


    return 0;
}


