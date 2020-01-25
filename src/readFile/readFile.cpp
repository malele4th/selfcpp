/* ========================================================
 *   Copyright (C) 2019 All rights reserved.
 *   
 *   filename : readFile.cpp
 *   author   : malele@360.cn
 *   date     : 2019-12-31
 *   info     : 
 * ======================================================== */

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<stdlib.h> 

#include "readFile.h"
#include "splitString.h"
using namespace std;

ReadFile::ReadFile(){
}

ReadFile::~ReadFile(){
}

int ReadFile::read_file_line(const char *file_name, vector<string>& file_line_vec){
    fstream fin;
    fin.open(file_name, ios::in);
    if(fin.fail()){
        cout<<"=== file open fail:\t"<< file_name <<endl;
        return -1;
    }

    string line;
    while(getline(fin, line)){
        if(line.size() <= 0) continue;
        file_line_vec.push_back(line);
    }
    return 0;
}


int ReadFile::read_file_key_vec(const char *file_name, map<string, vector<string> >& key_vec_map){
    fstream fin;
    fin.open(file_name, ios::in);
    if(fin.fail()){
        cout<<"=== file open fail:\t"<< file_name <<endl;
        return -1;
    }

    string line;
    while(getline(fin, line)){
        vector<string> line_vec;
        string key;
        vector<string> vec;
         
        if(line.size() <= 0) continue;
        split_string(line, "\t", line_vec);
        if(line_vec.size() < 2) continue;
        key = line_vec[0];
        for(int i=1; i < line_vec.size(); i++){
            vec.push_back(line_vec[i]);
        }
        key_vec_map[key] = vec;
    }
    return 0;
}

int ReadFile::read_file_key_emb(const char *file_name, map<string, vector<float> >& key_vec_map){
    fstream fin;
    fin.open(file_name, ios::in);
    if(fin.fail()){
        cout<<"=== file open fail:\t"<< file_name <<endl;
        return -1;
    }

    string line;
    while(getline(fin, line)){
        vector<string> line_vec;
        string key;
        vector<float> vec;
         
        if(line.size() <= 0) continue;
        split_string(line, "\t", line_vec);
        if(line_vec.size() < 2) continue;
        key = line_vec[0];
        for(int i=1; i < line_vec.size(); i++){
            vec.push_back(atof(line_vec[i].c_str()));
        }
        key_vec_map[key] = vec;
    }
    return 0;
}


int ReadFile::read_file_vec_vec(const char *file_name, vector<string>& key_vec, vector<vector<float> >& data_vec_vec){
    fstream fin;
    fin.open(file_name, ios::in);
    if(fin.fail()){
        cout<<"=== file open fail:\t"<< file_name <<endl;
        return -1;
    }

    string line;
    while(getline(fin, line)){
        if(line.size() <= 0) continue;
        vector<string> line_vec;
        split_string(line, "\t", line_vec);
        if(line_vec.size() < 2) continue;
        key_vec.push_back(line_vec[0]);  // out key
        vector<float> vec;
        for(int i=1; i < line_vec.size(); i++){
            vec.push_back(atof(line_vec[i].c_str()));
        }
        data_vec_vec.push_back(vec); // out data
    }
    return 0;
}


