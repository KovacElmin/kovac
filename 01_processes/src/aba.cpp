#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>

using namespace std;

int main(){
    auto pid{fork()};
    if(pid == 0){
        while(true){
            cout << "A" << flush;
            chrono::milliseconds sleeptime(500);
            this_thread::sleep_for(sleeptime);
        }
    }else{
        for(int i = 0; i < 6; i++){
            cout << "B" << flush;
            chrono::milliseconds sleeptime(500);
            this_thread::sleep_for(sleeptime);
        }
        /*
        Parent Prozess kriegt bei der fork Funktion
        bei der pid Variable die echte process id
        des child Prozesses zurück
        */
        kill(pid, SIGKILL);
        quick_exit(EXIT_SUCCESS);
        
    }
}