#include "clock.h"
#include <iostream>
#include <string>
#include <thread>

using namespace std;

class TimeSlave{
private:
    string name_;
    int hours_, minutes_, seconds_;
public:
    TimeSlave(string name_, int hours_, int minutes_, int seconds_)
    : name_(name_), hours_(hours_), minutes_(minutes_), seconds_(seconds_){}
    
    void operator()(){
        thread clock(Clock(name_, hours_, minutes_, seconds_));
        clock.join();
    }
};

int main(){
    thread slave1{TimeSlave("slave1", 15, 45, 0)};
    thread slave2{TimeSlave("slave2", 20, 25, 0)};

    slave1.join();
    slave2.join();
    
}