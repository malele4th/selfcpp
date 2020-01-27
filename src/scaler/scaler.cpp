/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : scaler.cpp
 *   author   : malele@360.cn
 *   date     : 2020-01-26
 *   info     : 
 * ======================================================== */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>

#include "readFile.h"
#include "scaler.h"

using namespace std;


// 标准化基类

ScalerBase::ScalerBase(){
}

ScalerBase::~ScalerBase(){
}


// 0-1最大最小标准化
ScalerMinMax::ScalerMinMax(){
}

ScalerMinMax::~ScalerMinMax(){
}

void ScalerMinMax::fit(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set){
    // scaler_min_max = (x - min) / (max - min)
    data_max_vec = data_set[0];
    data_min_vec = data_set[0];
    // step 1
    for(int i = 1; i < data_set.size(); i++){
        for(int j = 0; j < data_set[i].size(); j++){
            if(data_set[i][j] < data_min_vec[j]){
                data_min_vec[j] = data_set[i][j];
            }
            if(data_set[i][j] > data_max_vec[j]){
                data_max_vec[j] = data_set[i][j];
            }
        }
    }
    for(int j = 0; j < data_min_vec.size(); j++){
        data_range_vec.push_back(data_max_vec[j] - data_min_vec[j]);
    }
    // step 2
    transform(data_set, scaler_data_set);
}

void ScalerMinMax::transform(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set){
    float EPS = 0.00001;
    for(int i = 0; i < data_set.size(); i++){
        vector<float> vec;
        for(int j = 0; j < data_set[i].size(); j++){
            if(data_range_vec[j] < EPS){
                vec.push_back(data_set[i][j]);
            }
            else{
                float scaler_val = (data_set[i][j] - data_min_vec[j]) / data_range_vec[j];
                vec.push_back(scaler_val);
            }
        }
        scaler_data_set.push_back(vec);
    }
}

// z_score 标准化
ScalerStandard::ScalerStandard(){
}

ScalerStandard::~ScalerStandard(){
}

void ScalerStandard::fit(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set){
    // z_score = (x - mu) / delte   N(0,1)  减去均值除以标准差
    vector<float> mu_vec(data_set[0].size(), 0.0);
    vector<float> delta_vec(data_set[0].size(), 0.0);
    // step 1 求均值
    for(int i = 0; i < data_set.size(); i++){
        for(int j = 0; j < data_set[i].size(); j++){
            mu_vec[j] += data_set[i][j] / data_set.size();
        }
    }
    // step 2 求标准差
    for(int i = 0; i < data_set.size(); i++){
        for(int j = 0; j < data_set[i].size(); j++){
            delta_vec[j] += pow(data_set[i][j] - mu_vec[j], 2) / data_set.size();
        }
    }
    for(int j = 0; j < delta_vec.size(); j++){
        delta_vec[j] = sqrt(delta_vec[j]);
    }
    // step 3
    data_mu_vec = mu_vec;
    data_delta_vec = delta_vec;
    transform(data_set, scaler_data_set);
}

void ScalerStandard::transform(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set){
    float EPS = 0.00001;
    for(int i = 0; i < data_set.size(); i++){
        vector<float> vec;
        for(int j = 0; j < data_set[i].size(); j++){
            if(data_delta_vec[j] < EPS){
                vec.push_back(0.0);
            }
            else{
                float scaler_val = (data_set[i][j] - data_mu_vec[j]) / (data_delta_vec[j]);
                vec.push_back(scaler_val);
            }
        }
        scaler_data_set.push_back(vec);
    }
}


