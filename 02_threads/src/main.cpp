#include <iostream>
#include <thread>
using namespace std;

void drive(){
    int i = 0;
    while(true){
        i++;
        cout << i << " VW Golf" << endl;
        this_thread::sleep_for(1s);
    }
}

int main() {
    return 0;
}
