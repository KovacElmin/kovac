#include "philosopher.h"
#include <iostream>
#include <thread>

using namespace std;

void Philosopher::operator()(){
    //if condition for deadlock security
    if(sp != nullptr){
        if(liveLock){
            //block for the philosopher simulation with deadlock security and livelock security
            while(true){
                println("Philosopher ", to_string(id), " is thinking");
                this_thread::sleep_for(std::chrono::milliseconds(1000));

                println("Philosopher ", to_string(id) , " attempts to get left fork");
                
                leftFork.lock();
                sp->acquire();
                println("Philosopher " , to_string(id) , " got the left fork. Now he wants the right one...");
                println("currently ", sp->available_permits(), " left forks available");
                
                bool gotRightLock = timed_mtx.try_lock_for(chrono::milliseconds(3000));
                cout << "GOTRIGHTLOCK: " << gotRightLock << endl;
                if(gotRightLock == false){
                    this_thread::sleep_for(std::chrono::milliseconds(100));
                    leftFork.unlock();
                    sp->release();
                    println("Philosopher ", id, " released left fork due to timeout getting the right one!");
                    this_thread::sleep_for(std::chrono::milliseconds(3000));
                }else{
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
            }
        }else{
            //block for the philosopher simulation with deadlock security and without livelock security
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
                
        }
    }else{
        if(liveLock){
            //block for the philosopher simulation without deadlock security and livelock security
            while(true){
                println("Philosopher ", to_string(id), " is thinking");
                this_thread::sleep_for(std::chrono::milliseconds(1000));

                println("Philosopher ", to_string(id) , " attempts to get left fork");
                
                leftFork.lock();
                println("Philosopher " , to_string(id) , " got the left fork. Now he wants the right one...");
                
                bool gotRightLock = timed_mtx.try_lock_for(chrono::milliseconds(3000));
                cout << "GOTRIGHTLOCK: " << gotRightLock << endl;
                if(gotRightLock == false){
                    this_thread::sleep_for(std::chrono::milliseconds(100));
                    leftFork.unlock();
                    println("Philosopher ", id, " released left fork due to timeout getting the right one!");
                    this_thread::sleep_for(std::chrono::milliseconds(3000));
                }else{
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
        }else{
            //block for the philosopher simulation without deadlock security and without livelock security
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