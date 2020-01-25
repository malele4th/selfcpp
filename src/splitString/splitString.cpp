/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : splitString.cpp
 *   author   : malele
 *   date     : 2020-01-03
 *   info     : 
 * ======================================================== */

#include <iostream>
#include <string>
#include <vector>

#include "splitString.h"

using namespace std;

void split_string(string str, string pattern, vector<string>& result){
    str += pattern;  // 扩展字符串以方便操作
    for(int i=0; i < str.size(); i++){
        int pos = str.find(pattern, i);
        if(pos < str.size()){
            string substr = str.substr(i, pos - i);
            result.push_back(substr);
            i = pos + pattern.size() - 1;
        }
    }
}


