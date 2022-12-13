#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "work_packet.h"

class WorkQueue{
private:
    std::mutex myMutex;
    std::queue<WorkPacket> myQueue;
    std::condition_variable not_empty;
    size_t size;
public:
    WorkQueue(size_t size):size(size){};
    void push(WorkPacket wp);
    WorkPacket pop();
};