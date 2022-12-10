#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <iomanip>
#include "work_packet.h"
#include "work_queue.h"

using namespace std;

void worker(int id, WorkQueue& q){
    while(true){
        cout << "W" << id << ": Want work packet" << endl;
        WorkPacket wp = q.pop();
        cout << "W" << id << ": Got work packet " << wp.getId() << endl;
        
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<double> dis{1, 10};

        double random_time = dis(gen);
        int millisecondsToSleep = random_time * 1000;

        chrono::milliseconds sleeptime(millisecondsToSleep);
        this_thread::sleep_for(sleeptime);

        cout << "W" << id << ": Processed work packet " << wp.getId() <<  "(" << setprecision(2) << random_time << "s)" << endl;
    }

}

int main(){
    WorkQueue wq;
    int i = 0;
    
    thread worker1{worker, 1, ref(wq)};
    thread worker2{worker, 2, ref(wq)};
    thread worker3{worker, 3, ref(wq)};


    while(true){
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<double> dis{0, 1};

        double random_time = dis(gen);
        int millisecondsToSleep = random_time * 1000;
        
        cout << "B: Waiting to submit work packet " << i << endl;
        
        chrono::milliseconds sleeptime(millisecondsToSleep);
        this_thread::sleep_for(sleeptime);

        WorkPacket wp(i);
        wq.push(wp);
        cout << "B: Submitted work packet " << i <<  "(" << setprecision(2) << random_time << "s)" << endl;
        i++;
    }

    worker1.join();
    worker2.join();
    
}
