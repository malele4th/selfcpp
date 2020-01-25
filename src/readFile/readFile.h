/* ========================================================
 *   Copyright (C) 2019 All rights reserved.
 *   
 *   filename : readFile.h
 *   author   : malele@360.cn
 *   date     : 2019-12-31
 *   info     : 
 * ======================================================== */

#ifndef _READFILE_H
#define _READFILE_H

#include<fstream>
#include<vector>
#include<string>
#include<map>

#include "splitString.h"
using namespace std;

class ReadFile{
    public:
        ReadFile();
        ~ReadFile();
        int read_file_line(const char *file_name, vector<string>& file_line_vec);
        int read_file_key_vec(const char *file_name, map<string, vector<string> >& key_vec_map);
        int read_file_key_emb(const char *file_name, map<string, vector<float> >& key_vec_map);
        int read_file_vec_vec(const char *file_name, vector<string>& key_vec, vector<vector<float> >& data_vec_vec);
};

#endif //READFILE_H


