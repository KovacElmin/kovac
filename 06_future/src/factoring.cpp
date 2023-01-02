#include <iostream>
#include <future>
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
    future<vector<vector<InfInt>>> futureResults = async(launch::async, getAllPrimes, results, vec);
    
    while(futureResults.wait_for(chrono::seconds(1)) == future_status::ready){
        results = futureResults.get();
        cout << results.size() << endl;
        for(long unsigned int i = 0; i < results.size(); i++){
            cout << vec[i] << ": ";
            for(long unsigned int j = 0; j < results[i].size(); j++){
                cout << results[i][j] << " ";
            }
            cout << endl;
        }
    } 
    
}