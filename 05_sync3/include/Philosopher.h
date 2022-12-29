#pragma once

#include <mutex>
#include <vector>

class Philosopher{
private:
    int id;
    std::mutex& leftFork;
    std::mutex& rightFork;
    std::mutex globalMutex;
public: 
    Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork) 
    : id(id), leftFork(leftFork), rightFork(rightFork){};
    void operator()();
    void println(const std::initializer_list<std::string>& list);
};