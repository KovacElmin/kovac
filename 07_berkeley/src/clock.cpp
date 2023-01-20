#include "clock.h"
#include "timeutils.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void Clock::operator()(){
    int passedSeconds = 0;
    while (true)
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        chrono::system_clock systemClock;
        chrono::time_point<chrono::system_clock> currTime = systemClock.now();
        chrono::time_point<chrono::system_clock> editedTime = set_time(currTime, hours_, minutes_, seconds_);
        editedTime += chrono::seconds(passedSeconds);
        cout << name_ << ": " << editedTime << endl;
        passedSeconds++;
    }
    
    


}