/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : kmeans.h
 *   author   : malele@360.cn
 *   date     : 2020-01-09
 *   info     : 
 * ======================================================== */

#ifndef _KMEANS_H
#define _KMEANS_H

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<ctime>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "readFile.h"
#include "splitString.h"
#include "scaler.h"

using namespace std;
/*

[c++实现kmeans]  https://blog.csdn.net/lavorange/article/details/28854929
[聚类效果的评价指标]  https://blog.csdn.net/chixujohnny/article/details/51852633
数据噪声、样本密度差异、各个簇之间距离的远近、数据倾斜，都会影响聚类的效果


聚类效果的评价指标： 簇内样本距离尽量的近，簇与簇之间的样本尽量的远
Calinski-Harabaz（CH）
CH指标通过计算类中各点与类中心的距离平方和来度量类内的紧密度，通过计算各类中心点与数据集中心点距离平方和来度量数据集的分离度，CH指标由分离度与紧密度的比值得到。
从而，CH越大代表着类自身越紧密，类与类之间越分散，即更优的聚类结果。
在scikit-learn中， Calinski-Harabasz Index对应的方法是metrics.calinski_harabaz_score.


kmeans++只是选取初始簇心与kmeans不同
第一个簇心随机选取; 选取第n+1个聚类中心时：距离当前n个聚类中心越远的点会有更高的概率被选为第n+1个聚类中心
(1) 随机选取一个样本作为第一个聚类中心
(2) 计算每个样本与当前已有类聚中心最短距离（即与最近一个聚类中心的距离），值越大表示被选取作为聚类中心的概率较大；最后用轮盘法选出下一个聚类中心
(3) 重复(2)，直至选出k个聚类中心

*/

class Kmeans{
    public:
        Kmeans(int k);
        Kmeans(int k, string rand_centroid_mode);
        Kmeans(int k, string rand_centroid_mode, string normalize_mode);
        ~Kmeans();

        void loadDataSet(const char *file_name);
        void loadDataSet(vector<vector<float> > &data_set, vector<string> &data_label); // 重载

        void runKmeans();
        void outputCluster(const char *output_file);
        float calinski_harabaz_score();  // ch_score 评估聚类效果的好坏，越大越好

    private:
        float distanceSquaredEuclidean(vector<float> &vec1, vector<float> &vec2);
        float closestDistanceToCentroid(vector<vector<float> > &CurrentCentroidVec, vector<float> &sample); // 计算样本到当前已有质心中，最近的距离, kmeans++用到

        void initRandSetCentroid();
        void initRandSetCentroidKpp();  // kmeans++选取初始簇心
        void initClusterAssment();
        void getDataCentroid(vector<vector<float> > &data, vector<float> &centroid); // ch_score用到

    private:
        ReadFile read_file;
        vector<vector<float> > dataSet; // 数据集
        vector<string> dataLabel;       // 样本标签 or 样本含义
        int dataNum;             // 数据集大小
        int dataDim;             // 数据集维度
        string randCentroidMode; // 随机选择质心的模式，kmeans, kmeans++两种
        string normalizeMode;    // 数据集归一化的模式，min_max, z_score两种

        int clusterNum;          // 聚类的簇数
        vector<vector<float> > centroidVec;       // 存放簇中心
        vector<pair<int, float> > clusterAssment; // 存放每个样本所属簇的索引，以及距离该簇的距离

};

#endif //KMEANS_H


