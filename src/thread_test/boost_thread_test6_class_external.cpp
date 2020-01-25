/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : 
 *   author   : malele@360.cn
 *   date     : 2020-01-07
 *   info     : 在类外用类内部函数创建线程 
 * ======================================================== */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <string>
#include <iostream> 


using namespace std;

class HelloWorld
{
    public:
        void hello(const std::string& str1, const std::string& str2){
            std::cout << str1 <<" "<< str2 << std::endl;
        }
}; 
 

class SumTest{
    public:
        SumTest(int x); 
        int sum_int(int& a, int& b, int& res);
        void test();

    public:
        vector<int> res_sum;
        vector<int> add1;
        vector<int> add2;
        int loop_num;
};

SumTest::SumTest(int x){ 
    loop_num = x;
    for(int i=0;i<x;i++){
        add1.push_back(i);
        add2.push_back(i);
        res_sum.push_back(0);
    }   
}

int SumTest::sum_int(int& a, int& b, int& res){
    cout<<"&& a,b = "<<a<<" "<<b<<endl;
    res = a + b;
    return 1;
}

 
int main(int argc, char* argv[])
{ 
    HelloWorld hello_obj;
    for(int i=0; i<5; i++){
        boost::thread thrd( boost::bind(&HelloWorld::hello, &hello_obj, "hello world!", " haha") ) ;
        thrd.join();
    }

    int num = 5;
    SumTest sumtest(num);
    boost::thread_group bt_group;
    for(int i=0; i<num; i++){
        // method 1
        //sumtest.sum_int(sumtest.add1[i], sumtest.add2[i], sumtest.res_sum[i]);

        // method 2
        //boost::thread thr(boost::bind(&SumTest::sum_int, &sumtest, boost::ref(sumtest.add1[i]), boost::ref(sumtest.add2[i]), boost::ref(sumtest.res_sum[i])));
        //thr.join();

        bt_group.create_thread( boost::bind(&SumTest::sum_int, &sumtest, boost::ref(sumtest.add1[i]), boost::ref(sumtest.add2[i]), boost::ref(sumtest.res_sum[i]))  );
    }
    bt_group.join_all();

    for(int i=0; i<num; i++){
        cout<<"res_sum = "<<sumtest.res_sum[i]<<endl;
    }
    
    return 0;
} 



