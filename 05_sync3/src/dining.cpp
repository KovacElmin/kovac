#include "Philosopher.h"
#include <iostream>
#include <thread>

using namespace std;

int main(){
    mutex firstFork;
    mutex secondFork;
    mutex thirdFork;
    mutex fourthFork;
    mutex fifthFork;

    Philosopher p1(1, firstFork, secondFork);
    Philosopher p2(2, secondFork, thirdFork);
    Philosopher p3(3, thirdFork, fourthFork);
    Philosopher p4(4, fourthFork, fifthFork);
    Philosopher p5(5, fifthFork, firstFork);

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