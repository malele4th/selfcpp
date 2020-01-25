/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : pthread_test2_param.cpp
 *   author   : malele@360.cn
 *   date     : 2020-01-04
 *   info     : 
 * ======================================================== */
#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;
 
#define NUM_THREADS 5

// 在线程回调中传递任意的数据类型
struct thread_data{
   int  thread_id;
   char *message;
};
 
void *PrintHello(void *thread_arg)
{
   struct thread_data *my_data;
   my_data = (struct thread_data *) thread_arg;
   cout << "Thread ID : " << my_data->thread_id <<endl;
   cout << " Message : " << my_data->message << endl;
   pthread_exit(NULL);
}


int main ()
{
   pthread_t threads[NUM_THREADS];
   struct thread_data td[NUM_THREADS];
 
   for(int i=0; i < NUM_THREADS; i++){
      td[i].thread_id = i;
      td[i].message = (char*)"This is message";
      int ret = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);

      if (ret != 0){
         cout << "Error:unable to create thread," << ret << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}


