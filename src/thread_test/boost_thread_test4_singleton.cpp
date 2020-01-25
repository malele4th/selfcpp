/* ========================================================
 *   Copyright (C) 2020 All rights reserved.
 *   
 *   filename : 
 *   author   : malele@360.cn
 *   date     : 2020-01-07
 *   info     : 在Singleton模式内部创建线程
 * ======================================================== */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <iostream> 


class HelloWorld
{
    public:
        void hello(){
            std::cout << "Hello world, a thread!" << std::endl;
        }
        
        static void start(){
            boost::thread thrd( boost::bind( &HelloWorld::hello,&HelloWorld::getInstance() ) ) ;
            thrd.join();
        }

        static HelloWorld& getInstance(){
            if ( !instance )
                instance = new HelloWorld;
            return *instance;
        }

    private: 
        HelloWorld(){}
        static HelloWorld* instance;
};


HelloWorld* HelloWorld::instance = 0; 


int main(int argc, char* argv[])
{
    HelloWorld::start();
    return 0;
} 


