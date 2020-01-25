/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : kmeans.cpp
 *   author   : malele@360.cn
 *   date     : 2020-01-09
 *   info     : 
 * ======================================================== */

#include "kmeans.h"
#include "readFile.h"
#include "splitString.h"

template<class T>
Kmeans<T>::Kmeans(){
}

template<class T>
Kmeans<T>::~Kmeans(){
}

template<class T>
void Kmeans<T>::print(T a){ 
    cout<< a <<endl;
}



int main(){
    cout<<"dddxxx"<<endl;
    Kmeans<int> kmeans;
    kmeans.print(56);

    const char *input_file  = "../data/itag_embedding";

    ReadFile read_file;
    map<string, vector<float> > key_vec_map;
    read_file.read_file_key_emb(input_file, key_vec_map);

    /*
    map<string, vector<float> >::iterator it;
    for(it = key_vec_map.begin(); it != key_vec_map.end(); it++){
        cout<< it->first <<endl;
    }
    */
}


