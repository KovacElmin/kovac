#include <iostream>
#include <thread>
#include <random>
#include <iomanip>
#include <sstream>
using namespace std;



void drive(string car_name){
    int i = 0;
    string outputString = "";
    ostringstream outputStream;
    
    while(true){
        i++;
        
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<> dis{1, 10};

        outputStream << to_string(i) <<  " " << car_name 
        << ": " << fixed << setprecision(2) << dis(gen) << "sek";
        
        cout << outputStream.str() + "\n" << flush;
        outputStream.str("");

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
