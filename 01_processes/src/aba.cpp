#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
    auto pid{fork()};
    if(pid == 0){
        while(true){
            cout << "A" << flush;
            sleep(1);
        }
    }
}