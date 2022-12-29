#include "Philosopher.h"
#include <iostream>
#include <thread>

using namespace std;

void Philosopher::operator()(){
    while(true){
        println("Philosopher ", to_string(id), " is thinking");
        chrono::milliseconds sleeptime(1000);
        this_thread::sleep_for(sleeptime);

        println("Philosopher ", to_string(id) , " attempts to get left fork");
        
        leftFork.lock();
        println("Philosopher " , to_string(id) , " got the left fork. Now he wants the right one...");
        
        rightFork.lock();
        println("Philosopher ", to_string(id) , " got the right fork. Now he is eating...");
        
        chrono::milliseconds sleeptime1(2000);
        this_thread::sleep_for(sleeptime1);
        println("Philosopher ", to_string(id) , " finished eating");
        
        leftFork.unlock();
        println("Philosopher ", to_string(id) , " released left fork");

        rightFork.unlock();
        println("Philosopher ", to_string(id) , " released right fork");
    }
    
}



void Philosopher::println() {
    std::lock_guard<std::recursive_mutex> lg{out_mtx};
    std::cout << std::endl;
}

template<typename T, typename... Rest>
void Philosopher::println(const T& word, const Rest&... rest) {
    std::lock_guard<std::recursive_mutex> lg{out_mtx};
    std::cout << word << ' ';
    println(rest...);
}