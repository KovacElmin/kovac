#include <iostream>
#include <thread>
#include <mutex>
#include "work_packet.h"
#include "work_queue.h"

using namespace std;

void worker(int id, WorkQueue& q){
    while(true){
        cout << "W" << id << ": Want work packet" << endl;
        WorkPacket wp = q.pop();
        cout << "W" << id << ": Got work packet " << wp.getId() << endl;
        chrono::milliseconds sleeptime(1000);
        this_thread::sleep_for(sleeptime);
        cout << "W" << id << ": Processed work packet " << wp.getId() << endl;
    }

}

int main(){
    WorkQueue wq;
    int i = 0;
    
    thread worker1{worker, 1, ref(wq)};
    thread worker2{worker, 2, ref(wq)};


    while(true){
        WorkPacket wp(i);
        wq.push(wp);
        cout << "B: Submitted work packet " << i << endl;
        chrono::milliseconds sleeptime(500);
        this_thread::sleep_for(sleeptime);
        i++;
    }

    worker1.join();
    worker2.join();
    
}
