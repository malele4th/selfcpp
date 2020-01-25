/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : 
 *   author   : malele@360.cn
 *   date     : 2020-01-06
 *   info     : 类内部创建多线程, boost::bind(), boost::thread_group 
 * ======================================================== */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <iostream> 

using namespace std;

class HelloWorld
{
    public:
        void hello(){
            std::cout << "Hello world, a thread!" << std::endl;
        }

        void start(){
            boost::function<void()> f = boost::bind(&HelloWorld::hello,this);
            boost::thread thrd(f);
            thrd.join();
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

void SumTest::test(){
    boost::thread_group bt_group;

    for(int i=0; i<loop_num; i++){
        //method 1
        //sum_int(i,i,res_sum[i]);
        
        //method 2
        //boost::thread thr(boost::bind(&SumTest::sum_int,this, boost::ref(i), boost::ref(i), boost::ref(res_sum[i]))); //不用boost::ref()不能正确传递参数
        //thr.join();

        // method 3
        bt_group.create_thread( boost::bind(&SumTest::sum_int,this, boost::ref(add1[i]), boost::ref(add2[i]), boost::ref(res_sum[i])) );
    }
    bt_group.join_all();

    for(int i=0;i<res_sum.size();i++){
        cout<<"== res_sum "<< res_sum[i] <<endl;
    }
}


int main(int argc, char* argv[])
{
    HelloWorld hello;
    hello.start();

    SumTest sumtest(5);
    sumtest.test();

    return 0;
}


