#include <iostream>
#include <thread>
#include <random>
using namespace std;



void drive(string car_name){
    int i = 0;
    string outputString = "";

    
    while(true){
        i++;
        outputString = to_string(i) + " " + car_name;
        cout << outputString + "\n" << flush;

        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<> dis{1, 10};
    

        int millisecondsToSleep = dis(gen) * 1000;
        chrono::milliseconds sleeptime(millisecondsToSleep);
        this_thread::sleep_for(sleeptime);
    }
}


class Car{
private:
    string car_name;

public:
    Car(string car_name){
        this->car_name=car_name;
    }

    void operator()(){
        drive(this->car_name);
    }

};


int main() {

    thread drivingRounds{drive, "VW Golf"};
    Car c("VW Caddy");
    thread drivingRoundsWithClass{c};

    drivingRoundsWithClass.join();
    drivingRounds.join();
}
