#include "clock.h"
#include "timeutils.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>


using namespace std;

void Clock::operator()(){
    int passedSeconds = 0;
    ostringstream outputStream;
    while (true)
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::chrono::system_clock systemClock;
        std::chrono::time_point<chrono::system_clock> currTime = systemClock.now();
        editedTime = TIME_UTILS_H::set_time(currTime, hours_, minutes_, seconds_);

        editedTime += chrono::seconds(passedSeconds);
        
        outputStream << name_ << ": " << editedTime;
        cout << outputStream.str() + "\n" << flush;
        outputStream.str("");
        
        passedSeconds++;
    }
    
    


}

void Clock::set_time(int hours_, int minutes_, int seconds_){
    this->hours_ = hours_;
    this->minutes_ = minutes_;
    this->seconds_ = seconds_;
}

tuple<int,int,int> Clock::get_time(){
    tuple<int,int,int> time{hours_, minutes_, seconds_};
    return time;
}

long Clock::to_time(){
    long to_time = chrono::system_clock::to_time_t(editedTime);
    return to_time;
}

void Clock::from_time(long time){
    editedTime = chrono::system_clock::from_time_t(time);
}
