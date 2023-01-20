#include "clock.h"
#include <iostream>
#include <thread>

using namespace std;
int main(){
    thread clock{Clock("testclock")};
    clock.join();
}