#include <iostream>
#include "InfInt.h"
#include "CLI11.hpp"
#include "calc_factors.h"

using namespace std;


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

    vector<InfInt> results;
    for(InfInt elem : vec){
        results = get_factors(elem);
        cout <<  elem << ": ";
        for(InfInt resItem : results){
            cout << resItem << " ";
        }
        cout << endl;
        results.clear();
    }

    
    
}