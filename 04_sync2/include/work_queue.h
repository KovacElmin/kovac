#pragma once
#include <queue>
#include <mutex>
#include "work_packet.h"

class WorkQueue{
private:
    std::mutex myMutex;
    std::queue<WorkPacket> myQueue;
public:
    WorkQueue();
    void push(WorkPacket wp);
    WorkPacket pop();
};