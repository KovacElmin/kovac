#include <iostream>
#include <thread>
using namespace std;



void drive(string car_name){
    int i = 0;
    while(true){
        i++;
        cout << i << " " << car_name << endl;
        this_thread::sleep_for(1s);
    }
}

int main() {
    thread drivingRounds{drive, "VW Golf"};
    drivingRounds.join();
}
