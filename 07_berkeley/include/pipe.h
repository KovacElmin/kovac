#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe {
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
  public:
    Pipe& operator<<(T value) {
        if(!closed){
            unique_lock<mutex> guard{mtx};
            backend.push(value);
            not_empty.notify_one();
        }
        return *this;
    }
    
    Pipe& operator>>(T& value) {
        if(!closed){
            unique_lock<mutex> guard{mtx};
            not_empty.wait(guard, [this]{ return myQueue.size();});
            value = backend.front();
            backend.pop();
        }
        return *this;
    }

    void close() {
        unique_lock<mutex> guard{mtx};
        closed = true;
    }
    
    explicit operator bool() {
        unique_lock<mutex> guard{mtx};
        return !closed;
    }
};
#endif
