/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : scaler.h
 *   author   : malele@360.cn
 *   date     : 2020-01-25
 *   info     : 
 * ======================================================== */

#ifndef _SCALER_H
#define _SCALER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// scaler base
class ScalerBase{
    public:
        ScalerBase();
        ~ScalerBase();
        
    private:
        virtual void fit(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set) = 0;
        virtual void transform(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set) = 0;
};


// scaler min_max
class ScalerMinMax : public ScalerBase{
    public:
        ScalerMinMax();
        ~ScalerMinMax();
        void fit(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set);
        void transform(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set);

    private:
        vector<float> data_min_vec;
        vector<float> data_max_vec;
        vector<float> data_range_vec;
};


// scaler standard
class ScalerStandard : public ScalerBase{
    public:
        ScalerStandard();
        ~ScalerStandard();
        void fit(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set);
        void transform(vector<vector<float> > &data_set, vector<vector<float> > &scaler_data_set);

    private:
        vector<float> data_mu_vec;
        vector<float> data_delta_vec;
};

#endif //SCALER_H

