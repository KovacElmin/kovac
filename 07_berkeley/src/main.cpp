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
        Clock myClock(name_, hours_, minutes_, seconds_);
    }
};

int main(){
    thread clock{Clock("testclock", 15, 45, 0)};
    clock.join();
    
}