/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : 
 *   author   : malele@360.cn
 *   date     : 2020-01-06
 *   info     : 
 * ======================================================== */

#include <iostream> 
#include <boost/thread/thread.hpp> 
#include <boost/thread/mutex.hpp> 

//using namespace std; // 加上编译报错
boost::mutex io_mutex; 

//类重载operator()构成的函数创建线程
struct count 
{ 
    count(int id) : id(id) {} 
    void operator()() { 
        for (int i = 0; i < 10; ++i) { 
            boost::mutex::scoped_lock 
            lock(io_mutex); 
            std::cout << id << ": " << i << std::endl; 
        } 
    } 
    int id; 
}; 
  
int main(int argc, char* argv[]) 
{ 
    boost::thread thrd1(count(1)); 
    boost::thread thrd2(count(2)); 
    thrd1.join(); 
    thrd2.join(); 
    return 0; 
}



