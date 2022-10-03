#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <sys/wait.h>
#include <cstdlib>


using namespace std;

//AM ENDE NOCH KOMMENTARE HINZUFUEGEN
int main(){
    auto pid{fork()};
    if(pid == 0){   
        const char* aba_letter_a{getenv("ABA_LETTER_A")};
        if(aba_letter_a){
            execl("./charout", "charout", aba_letter_a, nullptr);
        }else{
            execl("./charout", "charout", "A", nullptr);
        }
        
        if(errno == -1){
            cout << "The program charout doesn't exist" << flush;
            exit(EXIT_FAILURE);
        }
            
    }else{
        auto pid1{fork()};

        if(pid1 == 0){
            const char* aba_letter_b{getenv("ABA_LETTER_B")};
            if(aba_letter_b){
                execl("./charout", "charout", aba_letter_b, nullptr);
            }else{
                execl("./charout", "charout", "B", nullptr);
            }
            if(errno == -1){
                cout << "The program charout doesn't exist" << flush;
                exit(EXIT_FAILURE);
            }
            
        }
        cout << "waiting for 3 seconds" << endl;
        sleep(3);

        cout << endl << "killing both subprocesses with pids " << pid 
             << " and " << pid1 << endl;
        kill(pid, SIGKILL);
        kill(pid1, SIGKILL);
        
        
        int status;
        
        cout<< "waiting for both subprocesses to be dead" << endl;
        waitpid(pid, &status, 0);
        waitpid(pid1, &status, 0);

        cout << "subprocess " << pid << " exited with " 
             << WEXITSTATUS(status) << endl;
        cout << "subprocess " << pid1 << " exited with " 
             << WEXITSTATUS(status) << endl;
        
        exit(EXIT_SUCCESS);
    }

        
  
        /*
        Parent Prozess kriegt bei der fork Funktion
        bei der pid Variable die echte process id
        des child Prozesses zurück
        */

       //NUMMER 9 NOCH NICHT .ABA FILE COMMITED
        
        
}