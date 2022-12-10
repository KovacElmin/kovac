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
public:
    WorkQueue();
    void push(WorkPacket wp);
    WorkPacket pop();
};