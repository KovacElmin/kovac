#include "work_queue.h"

using namespace std;

WorkQueue::WorkQueue(){

}

void WorkQueue::push(WorkPacket wp){
    lock_guard<mutex> guard{myMutex};
    myQueue.push(wp);
}

WorkPacket WorkQueue::pop(){
    lock_guard<mutex> guard{myMutex};
    WorkPacket poppedItem = myQueue.back();
    myQueue.pop();
    return poppedItem;
}