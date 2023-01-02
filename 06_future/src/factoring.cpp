#include <iostream>
#include <future>
#include <chrono>
#include "InfInt.h"
#include "CLI11.hpp"
#include "calc_factors.h"

using namespace std;

vector<vector<InfInt>> getAllPrimes(vector<vector<InfInt>> results, vector<InfInt> vec){
    for(InfInt elem : vec){
        results.push_back(get_factors(elem));
    }
    return results;
}

void print(vector<InfInt> vec, vector<vector<InfInt>> results){
    for(long unsigned int i = 0; i < results.size(); i++){
            cout << vec[i] << ": ";
            for(long unsigned int j = 0; j < results[i].size(); j++){
                cout << results[i][j] << " ";
            }
            cout << endl;
        }
}

void checkPrimeFactors(vector<InfInt> vec, vector<vector<InfInt>> results){
    InfInt res = 1;
    for(long unsigned int i = 0; i < results.size(); i++){
        for(long unsigned int j = 0; j < results[i].size(); j++){
            res *= results[i][j];
        }
        if(res != vec[i]){
            cerr << "Prime factors are not correct" << endl;
        }
        res = 1;
    }
}

int main(int argc, char* argv[]){
    vector<string> arguments;
    bool asynchron;

    CLI::App app("Factor numbers");
    app.add_option("number", arguments, "numbers to factor")
    ->required()->check([&](const string& str){
        if (str.find_first_not_of("1234567890") != string::npos){
            return str + " contains non numeric character";
        }
        return string();
    });
    app.add_flag("-a,--async", asynchron, "async");
    CLI11_PARSE(app, argc, argv);

    vector<InfInt> vec;
    for(string arg : arguments){
        vec.push_back(arg);
    }

    vector<vector<InfInt>> results;
    shared_future<vector<vector<InfInt>>> futureResults;
    auto start = chrono::system_clock::now();
    if(asynchron){
        futureResults = async(launch::async, getAllPrimes, results, vec);
    }else{
        futureResults = async(launch::deferred, getAllPrimes, results, vec);
    }
    
    //async anderer thread
    //deferred gleicher th
    while(futureResults.wait_for(chrono::seconds(3)) != future_status::ready){
        cout << "not ready" << endl;
    } 
    results = futureResults.get();
    thread t{print, vec, results};
    thread t1{checkPrimeFactors, vec, results};
    t.join();
    t1.join();
    
    auto duration = chrono::duration_cast<chrono::milliseconds>
        (chrono::system_clock::now() - start);
    cout << "Time elapsed used for factoring: " << duration.count() << "ms" << endl;
}