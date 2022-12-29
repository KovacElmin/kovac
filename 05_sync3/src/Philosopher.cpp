#include "Philosopher.h"
#include <iostream>
#include <thread>

using namespace std;

void Philosopher::operator()(){
    while(true){
        println({"Philosopher ", to_string(id), " is thinking"});
        chrono::milliseconds sleeptime(1000);
        this_thread::sleep_for(sleeptime);

        println({"Philosopher ", to_string(id) , " attempts to get left fork"});
        
        leftFork.lock();
        println({"Philosopher " , to_string(id) , " got the left fork. Now he wants the right one..."});
        
        rightFork.lock();
        println({"Philosopher ", to_string(id) , " got the right fork. Now he is eating..."});
        
        chrono::milliseconds sleeptime1(2000);
        this_thread::sleep_for(sleeptime1);
        println({"Philosopher ", to_string(id) , " finished eating"});
        
        leftFork.unlock();
        println({"Philosopher ", to_string(id) , " released left fork"});

        rightFork.unlock();
        println({"Philosopher ", to_string(id) , " released right fork"});
    }
    
}

void Philosopher::println(const vector<string>& v){
   lock_guard<mutex> lg{globalMutex};
   for(string item : v){
    cout << item;
   }
   cout << endl;
}