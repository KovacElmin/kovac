#include "philosopher.h"
#include <iostream>
#include <thread>

using namespace std;

void Philosopher::operator()(){
    if(sp != nullptr){
        while(true){
            println("Philosopher ", to_string(id), " is thinking");
            this_thread::sleep_for(std::chrono::milliseconds(1000));

            println("Philosopher ", to_string(id) , " attempts to get left fork");
            
            leftFork.lock();
            sp->acquire();
            println("Philosopher " , to_string(id) , " got the left fork. Now he wants the right one...");
            println("currently ", sp->available_permits(), " left forks available");
            

            rightFork.lock();
            println("Philosopher ", to_string(id) , " got the right fork. Now he is eating...");
            
            this_thread::sleep_for(std::chrono::milliseconds(2000));
            println("Philosopher ", to_string(id) , " finished eating");
            
            leftFork.unlock();
            sp->release();
            println("Philosopher ", to_string(id) , " released left fork");
            println("currently ", sp->available_permits(), " left forks available");
            
            this_thread::sleep_for(std::chrono::milliseconds(5000));

            rightFork.unlock();
            println("Philosopher ", to_string(id) , " released right fork");    
        }
    }else{
        while(true){
            println("Philosopher ", to_string(id), " is thinking");
            this_thread::sleep_for(std::chrono::milliseconds(1000));

            println("Philosopher ", to_string(id) , " attempts to get left fork");
            
            leftFork.lock();
            println("Philosopher " , to_string(id) , " got the left fork. Now he wants the right one...");
            
            rightFork.lock();
            println("Philosopher ", to_string(id) , " got the right fork. Now he is eating...");
            
            this_thread::sleep_for(std::chrono::milliseconds(2000));
            println("Philosopher ", to_string(id) , " finished eating");
            
            leftFork.unlock();
            println("Philosopher ", to_string(id) , " released left fork");

            this_thread::sleep_for(std::chrono::milliseconds(5000));

            rightFork.unlock();
            println("Philosopher ", to_string(id) , " released right fork");
        }
    }

    
    
}

void Philosopher::println() {
    lock_guard<recursive_mutex> lg{out_mtx};
    cout << endl;
}

template<typename T, typename... Rest>
void Philosopher::println(const T& word, const Rest&... rest) {
    lock_guard<std::recursive_mutex> lg{out_mtx};
    cout << word << ' ';
    println(rest...);
}