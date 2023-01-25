#include "clock.h"
#include "pipe.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>

using namespace std;


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

class TimeSlave{
private:
    string name_;
    int hours_, minutes_, seconds_;
    Channel* channel;
public:
    TimeSlave(string name_, int hours_, int minutes_, int seconds_)
    : name_(name_), hours_(hours_), minutes_(minutes_), seconds_(seconds_){}
    
    void operator()(){
        /*
        thread clock(Clock(name_, hours_, minutes_, seconds_));
        clock.join();
        */
        long value{};
        ostringstream outputStream;
        while(channel->get_pipe1() >> value){
            outputStream << name_ << " " << value;
            cout << outputStream.str() << "\n" << flush;
            outputStream.str("");
        }

    }

    void set_channel(Channel* ch){
        channel = ch;
    }

    Channel* get_channel(){
        return channel;
    }
};

class TimeMaster{
private:
    string name_;
    int hours_, minutes_, seconds_;
    Channel* channel1;
    Channel* channel2;
public:
    TimeMaster(string name_, int hours_, int minutes_, int seconds_)
    : name_(name_), hours_(hours_), minutes_(minutes_), seconds_(seconds_){}
    
    void operator()(){
        /*
        thread clock(Clock(name_, hours_, minutes_, seconds_));
        clock.join();
        */
        channel1->get_pipe1() << 1;
        channel1->get_pipe1() << 2;
        channel1->get_pipe1() << 3;

        channel2->get_pipe1() << 1;
        channel2->get_pipe1() << 2;
        channel2->get_pipe1() << 3;

        this_thread::sleep_for(chrono::milliseconds(500));

        channel1->get_pipe1().close();
        channel2->get_pipe2().close();
    }

    void set_channel1(Channel* ch1){
        channel1 = ch1;
    }

    void set_channel2(Channel* ch2){
        channel2 = ch2;
    }
};


int main(){
    Channel ch1;
    Channel ch2;

    TimeMaster master("master", 21, 0, 0);
    master.set_channel1(&ch1);
    master.set_channel2(&ch2);

    TimeSlave slave1("slave1", 15, 45, 0);
    slave1.set_channel(&ch1);

    TimeSlave slave2("slave2", 20, 25, 0);
    slave2.set_channel(&ch2);

    thread master_thread{master};
    thread slave1_thread{slave1};
    thread slave2_thread{slave2};

    master_thread.join();
    slave1_thread.join();
    slave2_thread.join();
    
}