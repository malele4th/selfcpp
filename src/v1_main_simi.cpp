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


void save_simi_table(const char *file_name, const map<string, vector<pair<string, float> > >& simi_table_map){
    fstream fout(file_name, ios::out);
    map<string, vector<pair<string, float> > >::const_iterator it;
    for(it = simi_table_map.begin(); it != simi_table_map.end(); it++){
        vector<string> key1_vec;
        split_string(it->first, "_", key1_vec);
        if(key1_vec.size() == 0) continue;
        string key1 = key1_vec[key1_vec.size()-1];
        fout << key1 << "\t";
        vector<pair<string, float> > simi_vec_pair = it->second;
        for(int i=0; i < simi_vec_pair.size(); i++){
            vector<string> key2_vec;
            split_string(simi_vec_pair[i].first, "_", key2_vec);
            if(key2_vec.size() == 0) continue;
            string key2 = key2_vec[key2_vec.size()-1];
            float score = simi_vec_pair[i].second;
            fout << key2 << "\x02" << score << "\x01";
        }
        fout << endl;
    }
    fout.close();
}

int main(int argc, char *argv[]){
    time_t start_time = time(0);
    cout<< "=== start time === " << ctime(&start_time) <<endl;
    const char *input_file  = "data/itag_embedding";
    const char *output_file = "data/itag_similarity";

    ReadFile read_file;
    map<string, vector<float> > key_vec_map;
    read_file.read_file_key_emb(input_file, key_vec_map);  // get [key, vec_emb] from file

    /*
    // method 1 每个itag分别计算K个相似itag
    Similarity similarity;
    map<string, vector<pair<string, float> > > simi_table_map;
    map<string, vector<float> >::iterator it;
    for(it = key_vec_map.begin(); it != key_vec_map.end(); it++){
        string key = it->first;
        vector<float> emb = it->second;
        vector<pair<string, float> > simi_vec_pair;
        similarity.cal_one_item_knn(emb, key_vec_map, 50, simi_vec_pair);
        simi_table_map[key] = simi_vec_pair;
    }
    save_simi_table(output_file, simi_table_map);
    */


    /*
    // method 2 批量itag分别计算K个相似itag
    Similarity similarity;
    map<string, vector<pair<string, float> > > simi_table_map;
    vector<map<string, vector<float> > > key_map_group;
    split_map_data(key_vec_map, 100, key_map_group);  // get key_vec_map group
    for(int i=0; i < key_map_group.size(); i++){
        map<string, vector<float> > map_batch = key_map_group[i];
        map<string, vector<pair<string, float> > > simi_batch_map;
        similarity.cal_batch_item_knn(map_batch, key_vec_map, 50, simi_batch_map);
        map<string, vector<pair<string, float> > >:: iterator it;
        for(it = simi_batch_map.begin(); it != simi_batch_map.end(); it++){
            simi_table_map[it->first] = it->second;
        }
    }
    save_simi_table(output_file, simi_table_map);
    */


    // method 3 批量itag, thread计算K个相似itag
    Similarity similarity;
    int num = 100;
    vector<map<string, vector<float> > > key_map_group;
    split_map_data(key_vec_map, num, key_map_group);  // get key_vec_map group
    vector< map<string, vector<pair<string, float> > > > simi_table_vec(100);

    boost::thread_group bt_group;
    for(int i=0; i < key_map_group.size(); i++){
        bt_group.create_thread( boost::bind(&Similarity::cal_batch_item_knn, &similarity, 
                                            boost::ref(key_map_group[i]), 
                                            boost::ref(key_vec_map), 
                                            50, 
                                            boost::ref( simi_table_vec[i]))  );
    }
    bt_group.join_all();

    map<string, vector<pair<string, float> > > simi_table_map;
    for(int i=0; i< simi_table_vec.size();i++){
        map<string, vector<pair<string, float> > > simi_batch_map = simi_table_vec[i];
        map<string, vector<pair<string, float> > >:: iterator it;
        for(it = simi_batch_map.begin(); it != simi_batch_map.end(); it++){
            simi_table_map[it->first] = it->second;
        }
    }
    save_simi_table(output_file, simi_table_map);

    time_t end_time = time(0);
    cout<< "=== simi_table_map.size() = "<< simi_table_map.size() <<endl;
    cout<< "===   end time === " << ctime(&end_time) <<endl;
    return 0;
}


