#pragma once

#include <mutex>
#include <condition_variable>

class Semaphor{
private:
    int counter = 1;
    std::mutex mtx;
    std::condition_variable cv;
public:
    Semaphor(){};
    Semaphor(int counter) : counter(counter){};
    void release();
    void acquire();
    int available_permits();
};