#include "clock.h"
#include "timeutils.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void Clock::operator()(){
    
    while (true)
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        chrono::system_clock systemClock;
        chrono::time_point<chrono::system_clock> curr_time = systemClock.now();
        cout << name_ << ": " << curr_time << endl;
    }
    
    


}