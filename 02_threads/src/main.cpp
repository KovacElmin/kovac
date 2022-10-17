#include <iostream>
#include <thread>
#include <random>
#include <iomanip>
#include <sstream>
using namespace std;



void drive(string car_name, double& total_time, int rounds){
    int i = 0;
    string outputString = "";
    ostringstream outputStream;
    double random_time = 0.00;

    while(i < rounds){
        i++;
        
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<> dis{1, 10};

        //determine a random number for the duration of the round
        random_time = dis(gen);

        //adding the current round time to the total time
        total_time += random_time;

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
    int rounds;

public:
    Car(string car_name){
        this->car_name=car_name;
    }

    void operator()(){
        drive(this->car_name, ref(this->total_time), this->rounds);
    }

    double get_total_time(){
        return total_time;
    }

    void set_rounds(int rounds){
        this->rounds = rounds;
    }

};

void help(){
    cout << "Usage: contest [-h | --help | LAPS]" << endl;
}

void error(string msg=""){
    if(msg == ""){
        cerr << "Run with --help for more information." << endl;
    }
    cerr << msg << endl;
}


int main(int argc, char* argv[]) {

    //Default value for rounds
    int rounds = 10;

    if(argc == 2){
        string parameter = argv[1];
        if(parameter == "-h" || parameter == "--help"){
            help();
            //exit code 0
            exit(EXIT_SUCCESS);
        }else{
            size_t pos;

            //trying to convert string to int
            try{
                stoi(parameter, &pos);
            }catch(...){
                error("");
                //exit code 1
                exit(EXIT_FAILURE);
            }
            if(pos == parameter.length()){
                if(stoi(parameter) < 1 || stoi(parameter) > 15){
                    error("Out of range (1 <= LAP'S < 16): " + parameter);
                    //exit code 1
                    exit(EXIT_FAILURE);
                }else{
                    //after validation -> set new value for rounds
                    rounds = stoi(parameter);
                }
                
            }else{
                error("");
                //exit code 1
                exit(EXIT_FAILURE);
            }
        }
    }


    double function_car_time{};

    //starting the thread with the function
    thread drivingRounds{drive, "VW Golf", ref(function_car_time), rounds};
    
    Car c("VW Caddy");
    c.set_rounds(rounds);
    //starting the thread with the class
    thread drivingRoundsWithClass{ref(c)};

    drivingRoundsWithClass.join();
    drivingRounds.join();

    //determine the winner
    if(c.get_total_time() > function_car_time){
        cout << "Sieger ist: VW Golf mit " << function_car_time << "sek" << endl;
        cout << "Verlierer ist: VW Caddy mit " << c.get_total_time() << "sek" << endl;
    }else{
        cout << "Sieger ist: VW Caddy mit " << c.get_total_time() << "sek" << endl;
        cout << "Verlierer ist: VW Golf mit " << function_car_time << "sek" << endl;
    }
    
}
