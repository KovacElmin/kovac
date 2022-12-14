#include "work_queue.h"
#include <iostream>

using namespace std;

void WorkQueue::push(WorkPacket wp){
    if(myQueue.size() < size){
        unique_lock<mutex> guard{myMutex};
        myQueue.push(wp);
        not_empty.notify_one();
    }
}

WorkPacket WorkQueue::pop(){
    unique_lock<mutex> guard{myMutex};
    not_empty.wait(guard, [this]{ return myQueue.size();});
    WorkPacket poppedItem = myQueue.front();
    myQueue.pop();
    return poppedItem;
    
}