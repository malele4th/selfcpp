/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : similarity.cpp
 *   author   : malele@360.cn
 *   date     : 2020-01-03
 *   info     : 
 * ======================================================== */

#include "similarity.h"

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<algorithm>

using namespace std;

bool pair_string_float_cmp(const pair<string, float>& a, const pair<string, float>& b){
    return a.second > b.second;
}

Similarity::Similarity(){
}

Similarity::~Similarity(){
}

float Similarity::cal_similarity(const vector<float>& vec1, const vector<float>& vec2, string mode){
    if(vec1.size() != vec2.size()){
        return -1.0;
    }
    
    if(mode.compare("cosine") == 0){
        float num  = 0.0;
        float den1 = 0.0;
        float den2 = 0.0;
        float simi = 0.0;
        for(int i=0; i < vec1.size(); i++){
            num  += vec1[i] * vec2[i];
            den1 += pow(vec1[i], 2);
            den2 += pow(vec2[i], 2);
        }

        simi = num / (sqrt(den1) * sqrt(den2));
        simi = simi * 0.5 + 0.5;
        return simi;
    }

    else if(mode.compare("euclidean") == 0){
        float distance = 0.0;
        float simi = 0.0;
        for(int i=0; i < vec1.size(); i++){
            distance += pow(vec1[i]-vec2[i], 2);
        }
        distance = sqrt(distance);
        simi = 1.0 / (1.0 + distance);
        return simi;
    }

    else{
        return -1.0;
    }

}

void Similarity::cal_one_item_knn(const vector<float>& emb, const map<string, vector<float> >& key_vec_map, int knn_num, vector<pair<string, float> >& result){
    map<string, float> simi_map;
    map<string, vector<float> >::const_iterator it;
    for(it = key_vec_map.begin(); it != key_vec_map.end(); it++){
        float simi = cal_similarity(emb, it->second, "cosine");
        simi_map[it->first] = simi;
    }
    
    vector<pair<string, float> > simi_vec_pair;
    for(map<string, float>::iterator it_simi = simi_map.begin(); it_simi != simi_map.end(); it_simi++){
        simi_vec_pair.push_back( pair<string, float>(it_simi->first, it_simi->second) );
    }
    sort(simi_vec_pair.begin(), simi_vec_pair.end(), pair_string_float_cmp);
    for(int i=1; i < simi_vec_pair.size(); i++){
        if(i >= knn_num + 1) break;
        result.push_back( pair<string, float>(simi_vec_pair[i].first, simi_vec_pair[i].second) );
    }
}


void Similarity::cal_batch_item_knn(const map_str_vec_float& key_emb_map, const map_str_vec_float& key_vec_map, int knn_num, map_str_vec_pair_str_float& simi_table_map){
    map_str_vec_float::const_iterator it;
    for(it = key_emb_map.begin(); it != key_emb_map.end(); it++){
        string key = it->first;
        vector<float> emb = it->second;
        vector<pair<string, float> > simi_vec_pair;
        cal_one_item_knn(emb, key_vec_map, knn_num, simi_vec_pair); // 调用计算单个的
        simi_table_map[key] = simi_vec_pair;
    }
}



