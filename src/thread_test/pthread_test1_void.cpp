/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : pthread_test1_void.cpp 
 *   author   : malele@360.cn
 *   date     : 2020-01-04
 *   info     : 
 * ======================================================== */
#include<iostream>
#include<pthread.h>

using namespace std;

#define NUM_THREADS 5
 
// 线程的运行函数
void* say_hello(void* args)
{
    cout << "Hello Runoob！" << endl;
}

void *PrintHello(void *thread_id)
{  
   // 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
   int tid = *((int*)thread_id);
   cout << "Hello Runoob! 线程 ID, " << tid << endl;
   pthread_exit(NULL);
}

int main(){
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];
    int index[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        index[i] = i;
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        //int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        int ret = pthread_create(&tids[i], NULL, PrintHello, (void *)&(index[i]));

        if (ret != 0)
        {
           cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    pthread_exit(NULL);
}

