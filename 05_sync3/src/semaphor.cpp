#include "semaphor.h"
#include <mutex>

using namespace std;

void Semaphor::release(){
    unique_lock<mutex> ul{mtx};
    cv.notify_one();
    counter++;
}

void Semaphor::acquire(){
    unique_lock<mutex> ul{mtx};
    cv.wait(ul, [this]{return counter;});
    counter--;
}

int Semaphor::available_permits(){
    lock_guard<mutex> guard{mtx};
    return counter;
}