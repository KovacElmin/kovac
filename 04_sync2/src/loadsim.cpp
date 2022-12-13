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
        //processing work packets
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

int main(int argc, char* argv[]){
    //size of the queue
    int size;

    if(argc == 2){
        string parameter = argv[1];
        if(parameter == "-h" || parameter == "--help"){
            cout << "Boss and worker simulation" << endl
                 << "Usage: loadsim [OPTIONS] size" << endl << endl
                 << "Positionals: " << endl
                 << "   size UINT REQUIRED      Size of the queue" << endl << endl
                 << "Options:" << endl
                 << "   -h, --help              Print this help message and exit" << endl;
            //exit code 0
            exit(EXIT_SUCCESS);
        }else {
            size_t pos; 
            //trying to convert string to int
            try{
                stoi(parameter, &pos);
            }catch(...){
                cerr << "Could not convert: size = " + parameter << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }
            if(pos == parameter.length()){
                size = stoi(parameter);
                if(size <= 0){
                    cerr << "Could not convert: size = " + parameter << endl
                         << "Run with --help for more information" << endl;
                    //exit code 1
                    exit(EXIT_FAILURE);
                }
            }else{
                cerr << "Could not convert: balance = " + parameter << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }
        }
    }else{
        cerr << "size is required" << endl
             << "Run with --help for more information." << endl;
        //exit code 1
        exit(EXIT_FAILURE);
    }

    WorkQueue wq(size);
    int i = 0;
    
    //starting worker threads
    thread worker1{worker, 1, ref(wq)};
    thread worker2{worker, 2, ref(wq)};
    thread worker3{worker, 3, ref(wq)};


    //boss thread
    while(i < size){
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<double> dis{0, 1};

        double random_time = dis(gen);
        int millisecondsToSleep = random_time * 1000;
        
        cout << "B: Waiting to submit work packet " << i << endl;
        
        chrono::milliseconds sleeptime(millisecondsToSleep);
        this_thread::sleep_for(sleeptime);

        //submitting packages to queue
        WorkPacket wp(i);
        wq.push(wp);
        cout << "B: Submitted work packet " << i <<  "(" << setprecision(2) << random_time << "s)" << endl;
        i++;
    }

    worker1.join();
    worker2.join();
    
}
