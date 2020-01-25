/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : boost_thread_test1_simple.cpp
 *   author   : malele@360.cn
 *   date     : 2020-01-05
 *   info     : boost::bind() boost::thread_group 的使用 
 * ======================================================== */

#include<iostream>
#include<boost/thread/thread.hpp>
#include<boost/bind.hpp>
#include<vector>

using namespace std;

void hello(){
    cout << "Hello world!"<< endl;
}

void print_num(int num){
    cout<<"num = "<<num<<endl;
}

void print_num2(int a, int b){
    cout<<"a,b = "<< a <<" "<< b <<endl;
}

void print_num_addr(int& num){
    cout<<"num = "<<num<<endl;
}


int sum_int(int& a, int& b, int& result){
    cout<<"## a,b = "<< a << " "<<b<<endl;
    result = a + b;
    cout<<"## sum = "<<result<<endl;
    return 1;
}

int main(int argc, char* argv[]){
    int a = 7;
    int b = 9;
   
    // step 1 普通的thread
    // 不传参数
    boost::thread thread_test1(&hello); 
    thread_test1.join();
    // 传参数，常量
    boost::thread thread_test2(&print_num, 5);
    thread_test2.join();
    // 传参数，变量
    boost::thread thread_test3(&print_num, b);
    thread_test3.join();
    // 传参数，多个常量
    boost::thread thread_test3_1(&print_num2, 12, 18);
    thread_test3_1.join();
    // 传参数，引用
    print_num_addr(a);
    boost::thread thread_test4(&print_num_addr, a);
    thread_test4.join();

    // step 2 使用 boost::bind()
    cout<<"\nboost::bind()"<<endl;
    // 不传参数
    boost::thread thread_test5(boost::bind(&hello));
    thread_test5.join();
    // 传参数，常量
    boost::thread thread_test6(boost::bind(&print_num, 90));
    thread_test6.join();
    // 传参数，变量
    boost::thread thread_test7(boost::bind(&print_num, b));
    thread_test7.join();
    // 传参数，引用
    boost::thread thread_test8(boost::bind(&print_num_addr, a));
    thread_test8.join();
    // 传参数，多个变量
    boost::thread thread_test9(boost::bind(&print_num2, a, b));
    thread_test9.join();
    // 使用 boost::ref()
    boost::thread thr1( boost::bind(&print_num2, boost::ref(a), boost::ref(b)) );
    thr1.join();
    
    // step 3 使用 boost::thread_group
    int res;
    sum_int(a,b,res);
    cout<<"** res = "<<res<<endl;
    
    int NUM = 5;
    vector<int> va;
    vector<int> vb;
    vector<int> vsum;
    for(int i=0;i<NUM;i++){
        va.push_back(i);
        vb.push_back(i);
        vsum.push_back(0);
    }

    cout<<"\nboost::thread_group"<<endl;
    boost::thread_group bt_group;
    for(int i=0; i<NUM; i++){
        cout<<"&& loop = "<< i <<endl;
        bt_group.create_thread( boost::bind( &sum_int, boost::ref(va[i]), boost::ref(vb[i]), boost::ref(vsum[i]) ) ); 
    }
    bt_group.join_all();

    for(int i=0;i<vsum.size();i++){
        cout<<"vsum "<<vsum[i]<<endl;
    }

}



