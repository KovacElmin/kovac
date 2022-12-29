#include "Philosopher.h"
#include <iostream>
#include <thread>

using namespace std;

void Philosopher::operator()(){
    while(true){
        cout << "Philosopher " << id << " is thinking" << endl;
    
        chrono::milliseconds sleeptime(1000);
        this_thread::sleep_for(sleeptime);

        cout << "Philosopher " << id << " attempts to get left fork" << endl;

        leftFork.lock();
        cout << "Philosopher " << id << " got the left fork. Now he wants the right one..." << endl;

        rightFork.lock();
        cout << "Philosopher " << id << " got the right fork. Now he is eating..." << endl;

        chrono::milliseconds sleeptime1(2000);
        this_thread::sleep_for(sleeptime1);
        cout << "Philosopher " << id << " finished eating" << endl;
        
        leftFork.unlock();
        cout << "Philosopher " << id << " released left fork" << endl;

        rightFork.unlock();
        cout << "Philosopher " << id << " released right fork" << endl;
    }
    
}