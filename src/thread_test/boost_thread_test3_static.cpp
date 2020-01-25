/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : 
 *   author   : malele@360.cn
 *   date     : 2020-01-06
 *   info     : 
 * ======================================================== */

#include <boost/thread/thread.hpp>
#include <iostream> 

// 在类内部对static函数创建线程
// start()和hello()方法都必须是static方法
//
class HelloWorld
{
    public:
        static void hello(){
            std::cout << "Hello world, I''m a thread!" << std::endl;
        }

        static void start(){
            boost::thread thrd(hello);
            thrd.join();
        }
};


int main(int argc, char* argv[]){
    HelloWorld::start();
    return 0;
}
