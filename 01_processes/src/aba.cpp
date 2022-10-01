#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <sys/wait.h>

using namespace std;

//AM ENDE NOCH KOMMENTARE HINZUFUEGEN
int main(){
    auto pid{fork()};
    if(pid == 0){
        while(true){
            execl("./charout", "charout", "A", nullptr);
            if(errno == -1){
                cout << "Das Programm charout existiert nicht";
                exit(EXIT_FAILURE);
            }
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

       //NUMMER 9 NOCH NICHT .ABA FILE COMMITED
        kill(pid, SIGKILL);
        int status;
        waitpid(pid, &status, 0);
        cout << "Kindprozess terminiert mit Exit Code "  << status << endl;
        quick_exit(EXIT_SUCCESS);
        
    }
}