#include "philosopher.h"
#include "semaphor.h"
#include <iostream>
#include <thread>
#include "CLI11.hpp"

using namespace std;

/*

NOCH NICHT 8 UND 9 COMMITED + CLI IST NOCH IN INCLUDE DATEI

*/
int main(int argc, char* argv[]){
    //Processing command line arguments with CLI
    CLI::App app("Dining philosophers simulation");

    bool noDeadLock = false;
    app.add_option("-n, --nodeadlock", noDeadLock,"Prevent a deadlock at all");
    bool liveLock = false;
    app.add_option("-l, --livelock", liveLock, "Simulate a livelock");
    CLI11_PARSE(app, argc, argv);

    //creating all forks for the Philosophers
    mutex firstFork;
    mutex secondFork;
    mutex thirdFork;
    mutex fourthFork;
    mutex fifthFork;

    if(noDeadLock){
        Semaphor sp(4);

        Philosopher p1(1, firstFork, secondFork, &sp, liveLock);
        Philosopher p2(2, secondFork, thirdFork, &sp, liveLock);
        Philosopher p3(3, thirdFork, fourthFork, &sp, liveLock);
        Philosopher p4(4, fourthFork, fifthFork, &sp, liveLock);
        Philosopher p5(5, fifthFork, firstFork, &sp, liveLock);

        thread philosopher1(ref(p1));
        thread philosopher2(ref(p2));
        thread philosopher3(ref(p3));
        thread philosopher4(ref(p4));
        thread philosopher5(ref(p5));

        philosopher1.join();
        philosopher2.join();
        philosopher3.join();
        philosopher4.join();
        philosopher5.join();
    }else{
        
        Philosopher p1(1, firstFork, secondFork, nullptr, liveLock);
        Philosopher p2(2, secondFork, thirdFork, nullptr, liveLock);
        Philosopher p3(3, thirdFork, fourthFork, nullptr, liveLock);
        Philosopher p4(4, fourthFork, fifthFork, nullptr, liveLock);
        Philosopher p5(5, fifthFork, firstFork, nullptr, liveLock);

        thread philosopher1(ref(p1));
        thread philosopher2(ref(p2));
        thread philosopher3(ref(p3));
        thread philosopher4(ref(p4));
        thread philosopher5(ref(p5));

        philosopher1.join();
        philosopher2.join();
        philosopher3.join();
        philosopher4.join();
        philosopher5.join();
    }
}