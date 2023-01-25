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

    void set_latency(long latency){
        pipe1.set_latency(latency);
        pipe2.set_latency(latency);
    }
};

class TimeSlave{
private:
    string name_;
    int hours_, minutes_, seconds_;
    Channel* channel;
    int deviation;
public:
    TimeSlave(string name_, int hours_, int minutes_, int seconds_, int deviation)
    : name_(name_), hours_(hours_), minutes_(minutes_), seconds_(seconds_), deviation(deviation){}
    
    void operator()(){
        Clock clock(name_, hours_, minutes_, seconds_, deviation);
        thread clock_thread(clock);
        long time = clock.to_time();
        long value;
        ostringstream outputStream;
        while(channel->get_pipe1() >> value){
            channel->get_pipe2() << time;
            channel->get_pipe1() >> value;
            clock.from_time(time + value);
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
    int deviation;
public:
    TimeMaster(string name_, int hours_, int minutes_, int seconds_, int deviation)
    : name_(name_), hours_(hours_), minutes_(minutes_), seconds_(seconds_), deviation(deviation){}
    
    void operator()(){
        Clock clock(name_, hours_, minutes_, seconds_, deviation);
        thread clock_thread(clock);

        while(true){
            long time = clock.to_time();


            channel1->get_pipe1() << time;
            channel2->get_pipe1() << time;
            long s1_time;
            channel1->get_pipe2() >> s1_time;
            long s2_time;
            channel2->get_pipe2() >> s2_time;
            long s1_deviation = s1_time - time;
            long s2_deviation = s2_time - time;
            long average_difference = (s1_deviation + s2_deviation) / 2;
            channel1->get_pipe1() << average_difference - s1_deviation;
            channel2->get_pipe1() << average_difference - s2_deviation;

            clock.from_time(time + average_difference);

            this_thread::sleep_for(chrono::milliseconds(10000));
        }

        clock_thread.join();
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

    ch1.set_latency(100);
    ch2.set_latency(200);

    TimeMaster master("master", 21, 0, 0, 200);
    master.set_channel1(&ch1);
    master.set_channel2(&ch2);

    TimeSlave slave1("slave1", 15, 45, 0, 300);
    slave1.set_channel(&ch1);

    TimeSlave slave2("slave2", 20, 25, 0, 400);
    slave2.set_channel(&ch2);

    thread master_thread{master};
    thread slave1_thread{slave1};
    thread slave2_thread{slave2};

    master_thread.join();
    slave1_thread.join();
    slave2_thread.join();
    
}