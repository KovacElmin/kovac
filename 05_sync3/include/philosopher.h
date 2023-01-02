#pragma once

#include <mutex>
#include <vector>
#include "semaphor.h"

class Philosopher{
private:
    int id;
    std::mutex& leftFork;
    std::mutex& rightFork;
    std::recursive_mutex out_mtx;
    std::timed_mutex timed_mtx;
    Semaphor* sp;
    bool liveLock;

public: 
    Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork, Semaphor *sp, bool liveLock) 
    : id(id), leftFork(leftFork), rightFork(rightFork), sp(sp), liveLock(liveLock){};
    void operator()();
    void println();
    template<typename T, typename... Rest> void println(const T& word, const Rest&... rest);
};