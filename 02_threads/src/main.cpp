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
    double random_time = 0.00;
    
    while(i < 10){
        i++;
        
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<> dis{1, 10};

        random_time = dis(gen);

        outputStream << to_string(i) <<  " " << car_name 
        << ": " << fixed << setprecision(2) << random_time << "sek";
        
        cout << outputStream.str() + "\n" << flush;
        outputStream.str("");

        int millisecondsToSleep = random_time * 1000;
        chrono::milliseconds sleeptime(millisecondsToSleep);
        this_thread::sleep_for(sleeptime);
    }
}


class Car{
private:
    string car_name;
    double total_time;

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
