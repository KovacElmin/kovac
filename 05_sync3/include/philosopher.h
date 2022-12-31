#pragma once

#include <mutex>
#include <vector>

class Philosopher{
private:
    int id;
    std::mutex& leftFork;
    std::mutex& rightFork;
    std::recursive_mutex out_mtx;
public: 
    Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork) 
    : id(id), leftFork(leftFork), rightFork(rightFork){};
    void operator()();
    void println();
    template<typename T, typename... Rest> void println(const T& word, const Rest&... rest);
};