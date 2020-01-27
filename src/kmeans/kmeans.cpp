/* ========================================================
 *   Copyright (C) 2019 All rights reserved.
 *   
 *   filename : kmeans.cpp
 *   author   : malele@360.cn
 *   date     : 2020-01-09
 *   info     : 
 * ======================================================== */

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<ctime>
#include<float.h>  // for FLT_MAX
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "kmeans.h"
#include "readFile.h"
#include "splitString.h"
#include "scaler.h"

using namespace std;


Kmeans::Kmeans(int k){
    clusterNum = k;
}

Kmeans::Kmeans(int k, string rand_centroid_mode){
    clusterNum = k;
    randCentroidMode = rand_centroid_mode;
}

Kmeans::Kmeans(int k, string rand_centroid_mode, string normalize_mode){
    clusterNum = k;
    randCentroidMode = rand_centroid_mode;
    normalizeMode = normalize_mode;
}

Kmeans::~Kmeans(){

}


void Kmeans::loadDataSet(const char *file_name){
    read_file.read_file_vec_vec(file_name, dataLabel, dataSet);
    dataNum = dataSet.size();
    dataDim = dataSet[0].size();
    cout<<"==== Kmeans::loadDataSet() : dataNum, dataDim = "<< dataNum <<", "<< dataDim<<endl;
}


void Kmeans::loadDataSet(vector<vector<float> > &data_set, vector<string> &data_label){
    dataLabel = data_label;
    dataSet = data_set;
    dataNum = dataSet.size();
    dataDim = dataSet[0].size();
    cout<<"==== Kmeans::loadDataSet() : dataNum, dataDim = "<< dataNum <<", "<< dataDim<<endl;
}


float Kmeans::distanceSquaredEuclidean(vector<float> &vec1, vector<float> &vec2){
    float distance_squared = 0.0;
    for(int i=0; i < vec1.size(); i++){
        distance_squared += pow(vec1[i]-vec2[i], 2); 
    }
    return distance_squared;
}


float Kmeans::closestDistanceToCentroid(vector<vector<float> > &CurrentCentroidVec, vector<float> &sample){
    float min_distance = FLT_MAX;
    for(int i = 0; i < CurrentCentroidVec.size(); i++){
        float distance = distanceSquaredEuclidean(CurrentCentroidVec[i], sample);
        if(distance < min_distance){
            min_distance = distance;
        }
    }
    return min_distance;
}


void Kmeans::initRandSetCentroid(){
    //cout<<"==== Kmeans::initRandSetCentroid() : enter here."<<endl;
    map<int, int> selected_index_map;
    srand(time(NULL)); // 伪随机，保证每次的随机值不一样, 调用srand(time(NULL))比较耗时
    while(centroidVec.size() < clusterNum){
        int index = rand() % dataNum;
        if( selected_index_map.find(index) != selected_index_map.end() ) continue;
        //cout<<"index = "<< index <<endl;
        selected_index_map[index] = 1;
        centroidVec.push_back(dataSet[index]);
    }
    cout<<"==== Kmeans::initRandSetCentroid() : centroidVec.size() = "<< centroidVec.size() <<endl;
}


void Kmeans::initRandSetCentroidKpp(){
    //cout<<"==== Kmeans::initRandSetCentroidKpp() : enter here." <<endl;
    // 第一个质心随机选取
    srand(time(NULL));
    int index = rand() % dataNum;
    centroidVec.push_back(dataSet[index]);
    // 选取其他质心
    vector<float> min_distance_vec;
    min_distance_vec.resize(dataNum);
    for(int i = 1; i < clusterNum; i++){
        float total_distance = 0.0;
        for(int j = 0; j < dataNum; j++){
            float min_distance = closestDistanceToCentroid(centroidVec, dataSet[j]);
            min_distance_vec[j] = min_distance;
            total_distance += min_distance;
        }
        // 轮盘选出下一个质心
        float rand_num = rand() % 1000 / 1000.0;
        total_distance *= rand_num;
        for(int j = 0; j < dataNum; j++){
            total_distance -= min_distance_vec[j];
            if(total_distance > 0) continue;
            centroidVec.push_back(dataSet[j]);
            break;
        }
    }
    cout<<"==== Kmeans::initRandSetCentroidKpp() : centroidVec.size() = "<< centroidVec.size() <<endl;
}


void Kmeans::initClusterAssment(){
    for(int i = 0; i < dataNum; i++){
        clusterAssment.push_back( pair<int, float>(-1, -1.0) );
    }
    cout<<"==== Kmeans::initClusterAssment() : clusterAssment.size() = "<< clusterAssment.size() <<endl;
}


void Kmeans::getDataCentroid(vector<vector<float> > &data, vector<float> &centroid){
    int num = data.size();
    int dim = data[0].size();
    centroid = data[0];
    for(int i = 1; i < num; i++){
        for(int j = 0; j < dim; j++){
            centroid[j] += data[i][j];
        }
    }
    for(int j=0; j < dim; j++){
        centroid[j] /= num;
    }
}


float Kmeans::calinski_harabaz_score(){
    float within_cluster_dispersion = 0.0;
    float between_cluster_dispersion = 0.0;
    vector<float> data_mean;
    getDataCentroid(dataSet, data_mean);
    for(int i = 0; i < clusterNum; i++){
        // 每个簇的数据集
        vector<vector<float> > cluster_data;
        for(int j = 0; j < dataNum; j++){
            if(clusterAssment[j].first == i){
                cluster_data.push_back(dataSet[j]);
            }
        }
        vector<float> cluster_mean = centroidVec[i];
        between_cluster_dispersion += cluster_data.size() * distanceSquaredEuclidean(cluster_mean, data_mean);
        for(int j = 0; j < cluster_data.size(); j++){
            within_cluster_dispersion += distanceSquaredEuclidean(cluster_data[j], cluster_mean);
        }
    }
    float coff = (dataNum - clusterNum) / (clusterNum - 1.0);
    float score = between_cluster_dispersion / within_cluster_dispersion * coff;
    //cout<<"ch_score,  between_disp,  within_disp,  coff = "<< score <<" "<<between_cluster_dispersion<<" "<< within_cluster_dispersion <<" "<< coff <<endl;
    cout<<"==== Kmeans::calinski_harabaz_score() : ch_score = "<< score <<endl;
    return score;
}


void Kmeans::runKmeans(){
    cout<<"==== Kmeans::runKmeans() : enter here."<<endl;
    
    // normalize data_set
    // scaler 在src目录下编译，kmeans.cpp报错， 但直接在main.cpp中使用不报错，暂时没解决
    if(normalizeMode == "z_score"){
        /*
        cout<<"==== Kmeans::runKmeans() : normalize z_score"<<endl;
        ScalerStandard scaler_obj;  
        vector<vector<float> > scaler_data_set;
        scaler_obj.fit(dataSet, scaler_data_set);
        dataSet = scaler_data_set;
        */
    }
    else if(normalizeMode == "min_max"){
        /*
        cout<<"==== Kmeans::runKmeans() : normalize min_max"<<endl;
        ScalerMinMax scaler_obj;
        vector<vector<float> > scaler_data_set;
        scaler_obj.fit(dataSet, scaler_data_set);
        dataSet = scaler_data_set;
        */
    }
    else{
        //cout<<"==== Kmeans::runKmeans() : normalize None"<<endl;
    }

    // kmeans or kmeans++
    if(randCentroidMode == "kmeans"){
        initRandSetCentroid();
    }
    else if(randCentroidMode == "kmeans++"){
        initRandSetCentroidKpp();
    }
    else{
        initRandSetCentroid();
    }

    // init cluster assment
    initClusterAssment();

    bool clusterChanged = true;
    int step = 0;
    while(clusterChanged){
        //if(step >= 2) break;
        /*
        if(step % 10 == 0){
            cout<<"#### running step = "<< step <<endl;
        }
        */
        step++;
        clusterChanged = false;

        // step 1 : find the nearest centroid of each sample
        // cout << "==== step 1 : find the nearest centroid of each sample." << endl;
        for(int i = 0; i < dataNum; i++){
            // 计算该样本与每个质心的距离，找出最近的质心索引
            //cout<<"  "<<endl;
            int minIndex = -1;
            float minDistance = FLT_MAX;
            for(int j = 0; j < clusterNum; j++){
                float distance = distanceSquaredEuclidean(dataSet[i], centroidVec[j]);
                //cout<<"j="<<j<<", dist = "<< distance <<endl;
                if(distance < minDistance){
                    minDistance = distance;
                    minIndex = j;
                }
            }

            //cout<< minIndex << "  "<< minDistance <<endl;
            // 如果该样本的质心发生变化，更新质心及 clusterChanged 状态
            if(clusterAssment[i].first != minIndex){
                clusterChanged = true;
                clusterAssment[i].first  = minIndex;
                clusterAssment[i].second = minDistance;
            }
        }

        // step 2: update centorid
        // cout << "step 2: update centorid." <<endl;
        for(int i = 0; i < clusterNum; i++){
            int sample_num = 0;                              // 存放属于每一簇的样本数
            vector<float> sample_vec_avg(dataDim, 0.0);  // 存放每一簇的样本向量均值，也就是更新后的质心
            // 找出同一个簇的所有样本，向量求和
            for(int j = 0; j < dataNum; j++){
                if(clusterAssment[j].first == i){
                    sample_num++;
                    for(int k = 0; k < dataDim; k++){
                        sample_vec_avg[k] += dataSet[j][k];
                    }
                }
            }

            //cout<<"sample_num = "<<sample_num<<endl;
            // 向量每一列，按行求均值, 并更新到质心向量中
            for(int k = 0; k < dataDim; k++){
                if(sample_num != 0){
                    sample_vec_avg[k] /= sample_num;
                }
                centroidVec[i][k] = sample_vec_avg[k];
            }
        }
        //cout<<endl;
    }
}


void Kmeans::outputCluster(const char *output_file){
    fstream fout(output_file, ios::out);
    for(int i = 0; i < dataNum; i++){
        int cluster_index = clusterAssment[i].first;
        string label = dataLabel[i];
        //cout<< label <<" "<<cluster_index<<endl;
        fout<< label <<"\t"<<cluster_index<<endl;
    }
    cout<<"==== Kmeans::outputCluster() "<<endl; 
}


/*
int main(int argc, char *argv[]){
    time_t start_time = time(0);
    cout<< "==== start time === " << ctime(&start_time) <<endl;

    const char *input_file  = "../data/itag_embedding";
    const char *output_file  = "../data/itag_kmeans_result";
    //const char *input_file  = "test_kmeans_input";
    //const char *output_file = "test_kmeans_output";
    
    vector<vector<float> > data_set;
    vector<string> data_label;
    ReadFile read_file;
    read_file.read_file_vec_vec(input_file, data_label, data_set);

    Kmeans kmeans(20, "kmeans++", "z_score");
    kmeans.loadDataSet(data_set, data_label);
    kmeans.runKmeans();
    kmeans.calinski_harabaz_score();
    kmeans.outputCluster(output_file);
    
    time_t end_time = time(0);
    cout<< "==== end time === " << ctime(&end_time) <<endl;
    return 0;
}
*/



