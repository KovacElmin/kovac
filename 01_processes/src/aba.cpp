#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <sys/wait.h>
#include <cstdlib>


using namespace std;

int main(){
    //forking for the first time
    auto pid{fork()};
    
    //if pid equals 0, then it is a subprocess
    if(pid == 0){   
        //trying to access environment variables
        const char* aba_letter_a{getenv("ABA_LETTER_A")};
        if(aba_letter_a){
            //executing the charout program
            execl("./charout", "charout", aba_letter_a, nullptr);
        }else{
            //executing the charout program
            execl("./charout", "charout", "A", nullptr);
        }
        
        if(errno == -1){
            cout << "The program charout doesn't exist" << flush;
            exit(EXIT_FAILURE);
        }
            
    }else{
        /*
        forking the process again in a code passage that the
        first subprocess can't access. This is important 
        because if I wouldn't do it this way there would
        be more than 2 subprocesses
        */
        auto pid1{fork()};

        //if pid1 equals 0, then it is a subprocess
        if(pid1 == 0){
            //trying to access environment variables
            const char* aba_letter_b{getenv("ABA_LETTER_B")};
            if(aba_letter_b){
                //executing the charout program
                execl("./charout", "charout", aba_letter_b, nullptr);
            }else{
                //executing the charout program
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
        /*
        the main process gets the real process id of it's children
        when using the pid variable
        */
        kill(pid, SIGKILL);
        kill(pid1, SIGKILL);
        
        
        int status;
        
        cout<< "waiting for both subprocesses to be dead" << endl;
        //waiting for the subprocesses to be dead in order to avoid zombies
        waitpid(pid, &status, 0);
        waitpid(pid1, &status, 0);

        cout << "subprocess " << pid << " exited with " 
             << WEXITSTATUS(status) << endl;
        cout << "subprocess " << pid1 << " exited with " 
             << WEXITSTATUS(status) << endl;
        
        //ending the program
        exit(EXIT_SUCCESS);
    }
}