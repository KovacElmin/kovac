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
            cout << "Das Programm charout existiert nicht" << flush;
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
                cout << "Das Programm charout existiert nicht" << flush;
                exit(EXIT_FAILURE);
            }
            
        }
        sleep(3);
        kill(pid, SIGKILL);
        kill(pid1, SIGKILL);
        int status;
        
        waitpid(pid, &status, 0);
        cout << "Kindprozess " << pid << " terminiert mit Exit Code "  << WEXITSTATUS(status) << endl;
        
        waitpid(pid1, &status, 0);
        cout << "Kindprozess " << pid1 << " terminiert mit Exit Code "  << WEXITSTATUS(status) << endl;
        
        exit(EXIT_SUCCESS);
    }

        
  
        /*
        Parent Prozess kriegt bei der fork Funktion
        bei der pid Variable die echte process id
        des child Prozesses zurück
        */

       //NUMMER 9 NOCH NICHT .ABA FILE COMMITED
        
        
}