#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
    auto pid{fork()};
    if(pid == 0){
        while(true){
            cout << "A" << flush;
            sleep(0.5);
        }
    }else{
        while(true){
            cout << "B" << flush;
            sleep(0.5);
        }
        
    }
}