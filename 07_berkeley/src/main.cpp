#include "clock.h"
#include "pipe.h"
#include <iostream>
#include <string>
#include <thread>

using namespace std;

class TimeSlave{
private:
    string name_;
    int hours_, minutes_, seconds_;
    Channel channel;
public:
    TimeSlave(string name_, int hours_, int minutes_, int seconds_)
    : name_(name_), hours_(hours_), minutes_(minutes_), seconds_(seconds_){}
    
    void operator()(){
        thread clock(Clock(name_, hours_, minutes_, seconds_));
        clock.join();
    }

    Channel* get_channel(){
        return &channel;
    }
};

class TimeMaster{
private:
    string name_;
    int hours_, minutes_, seconds_;
public:
    TimeMaster(string name_, int hours_, int minutes_, int seconds_)
    : name_(name_), hours_(hours_), minutes_(minutes_), seconds_(seconds_){}
    
    void operator()(){
        thread clock(Clock(name_, hours_, minutes_, seconds_));
        clock.join();
    }
};

class Channel{
private:
    Pipe<long> pipe1;
    Pipe<long> pipe2;
public:
    Pipe<long>& get_pipe1(){
        return pipe1;
    }

    Pipe<long>& get_pipe2(){
        return pipe2;
    }
};

int main(){
    thread master{TimeMaster("master", 21, 0, 0)};

    thread slave1{TimeSlave("slave1", 15, 45, 0)};
    thread slave2{TimeSlave("slave2", 20, 25, 0)};

    master.join();
    slave1.join();
    slave2.join();
    
}