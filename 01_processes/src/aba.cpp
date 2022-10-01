#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <sys/wait.h>


using namespace std;

int main(){
    auto pid{fork()};
    if(pid == 0){   
        execl("./charout", "charout", "A", nullptr);
        if(errno == -1){
            cout << "Das Programm charout existiert nicht" << flush;
            exit(EXIT_FAILURE);
        }
            
    }else{
        auto pid1{fork()};
        if(pid1 == 0){
            execl("./charout", "charout", "B", nullptr);
            if(errno == -1){
                cout << "Das Programm charout existiert nicht" << flush;
                exit(EXIT_FAILURE);
            }
            
        }
        sleep(3);
        /*
        Parent Prozess kriegt bei der fork Funktion
        bei der pid Variable die echte process id
        des child Prozesses zurück
        */
        kill(pid, SIGKILL);
        kill(pid1, SIGKILL);
        int status;
        
        waitpid(pid, &status, 0);
        cout << "Kindprozess " << pid << " terminiert mit Exit Code "  << WEXITSTATUS(status) << endl;
        
        waitpid(pid1, &status, 0);
        cout << "Kindprozess " << pid1 << " terminiert mit Exit Code "  << WEXITSTATUS(status) << endl;
        
        exit(EXIT_SUCCESS);
    }
        
}