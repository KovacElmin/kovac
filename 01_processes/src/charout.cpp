#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 2){
        cout << "Es muessen genau 2 "
             << "Kommandozeilenparameter "
             << "mitgegeben werden"
             << endl;
    }else{
        while(true){
            cout << argv[1] << flush;
            chrono::milliseconds sleeptime(500);
            this_thread::sleep_for(sleeptime);
        }
    }

}