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
    long latency;
  public:
    Pipe& operator<<(T value) {
        if(!closed){
            if(latency != 0){
                std::this_thread::sleep_for(std::chrono::milliseconds(latency));
            }
            std::unique_lock<std::mutex> guard{mtx};
            backend.push(value);
            not_empty.notify_one();
        }
        return *this;
    }
    
    Pipe& operator>>(T& value) {
        if(!closed){
            std::unique_lock<std::mutex> guard{mtx};
            not_empty.wait(guard, [this]{ return backend.size();});
            value = backend.front();
            backend.pop();
        }
        return *this;
    }

    void close() {
        std::unique_lock<std::mutex> guard{mtx};
        closed = true;
    }
    
    explicit operator bool() {
        std::unique_lock<std::mutex> guard{mtx};
        return !closed;
    }

    void set_latency(long latency){
        this->latency = latency;
    }
};
#endif
