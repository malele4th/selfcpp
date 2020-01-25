/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : similarity.h
 *   author   : malele@360.cn
 *   date     : 2020-01-03
 *   info     : 
 * ======================================================== */

#ifndef _SIMILARITY_H
#define _SIMILARITY_H

#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

typedef map<string, vector<float> > map_str_vec_float;
typedef vector<pair<string, float> > vec_pair_str_float;
typedef map<string, vector<pair<string, float> > > map_str_vec_pair_str_float;

class Similarity{
    public:
        Similarity();
        ~Similarity();

        float cal_similarity(const vector<float>& vec1, const vector<float>& vec2, string mode);
        
        void cal_one_item_knn(const vector<float>& emb, const map<string, vector<float> >& key_vec_map, int knn_num, vector<pair<string, float> >& result);
        void cal_batch_item_knn(const map_str_vec_float& key_emb_map, const map_str_vec_float& key_vec_map, int knn_num, map_str_vec_pair_str_float& simi_table_map);
};

#endif //SIMILARITY_H


