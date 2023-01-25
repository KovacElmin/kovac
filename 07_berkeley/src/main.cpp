#include "clock.h"
#include "pipe.h"
#include "CLI11.hpp"
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
        //Starten des Clock-Threads
        thread clock_thread(clock);
        long time = clock.to_time();
        long value;
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
        //starten des Clock-Threads
        thread clock_thread(clock);

        while(true){
            //Implementierung des berkeley Algorithmuses
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


int main(int argc, char* argv[]){
    //Eingabe der Latenzen und Abweichungen 
    CLI::App app("Simulate the berkeley-algo");

    bool monotone;
    app.add_flag("--monotone", monotone, "set monotone mode");

    unsigned int latency1;
    app.add_option("--latency1", latency1, "latency to channel 1 (both directions)");

    unsigned int latency2;
    app.add_option("--latency2", latency2, "latency to channel 2 (both directions)");

    int deviation1;
    app.add_option("--deviation1", deviation1, "deviation of clock of slave 1");

    int deviation2;
    app.add_option("--deviation2", deviation2, "deviation of clock of slave 2");

    int deviationm;
    app.add_option("--deviationm", deviationm, "deviation of clock of master");

    CLI11_PARSE(app, argc, argv);
    
    Channel ch1;
    Channel ch2;

    ch1.set_latency(latency1);
    ch2.set_latency(latency2);

    TimeMaster master("master", 21, 0, 0, deviationm);
    master.set_channel1(&ch1);
    master.set_channel2(&ch2);

    TimeSlave slave1("slave1", 15, 45, 0, deviation1);
    slave1.set_channel(&ch1);

    TimeSlave slave2("slave2", 20, 25, 0, deviation2);
    slave2.set_channel(&ch2);

    thread master_thread{master};
    thread slave1_thread{slave1};
    thread slave2_thread{slave2};

    master_thread.join();
    slave1_thread.join();
    slave2_thread.join();
    
}