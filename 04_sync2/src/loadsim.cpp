#include <iostream>
#include <thread>
#include "work_packet.h"
#include "work_queue.h"

using namespace std;

int main(){
	int i = 0;
    WorkQueue wq;
    while(true){
        WorkPacket wp(i);
        wq.push(wp);
        cout << "B: Submitted work packet " << i << endl;
        i++;
        chrono::milliseconds sleeptime(500);
        this_thread::sleep_for(sleeptime);
    }
}
