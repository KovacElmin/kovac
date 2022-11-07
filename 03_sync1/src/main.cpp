#include <iostream>
#include <thread>
#include "account.h"

using namespace std;

int main(int argc, char* argv[]){
    /*
    Punkt 1:
    Account myAccount(20);

    cout << "current balance: " 
    << myAccount.get_balance() << endl;

    cout << "trying to withdraw 25 Euros: "
    << myAccount.withdraw(25)
    << " | current Balance: "
    << myAccount.get_balance()
    << endl;

    cout << "trying to withdraw 10 Euros: "
    << myAccount.withdraw(10)
    << " | current Balance: "
    << myAccount.get_balance()
    << endl;

    cout << "depositing 20 Euros: ";
    myAccount.deposit(20);
    cout << " | current Balance: "
    << myAccount.get_balance()
    << endl;
    */

    /*    
    Punkt 5:
    Account myAccount(1);
    thread t1{[&]() {cout << "trying to withdraw 1 Euro: ";
                     string result = (myAccount.withdraw(1)) 
                                     ? "successful" : "not successful";
                     cout << result << endl;} };    
    thread t2{[&]() {cout << "trying to withdraw 1 Euro: ";
                     string result = (myAccount.withdraw(1)) 
                                     ? "successful" : "not successful";
                     cout << result << endl;} };

    */

    int deposits = 5;
    int balance = 0;

    if(argc < 2){
        cerr << "balance is required" << endl
             << "Run with --help for more information" << endl;
        exit(EXIT_FAILURE);
    }else if(argc == 2){
        string parameter = argv[1];
        if(parameter == "-h" || parameter == "--help"){
            std::cout << "Account app" << endl 
                 << "Usage: account [OPTIONS] balance" << endl << endl
                 << "Positionals:" << endl
                 << "  balance INT REQUIRED \t"
                 << "Initial balance" << endl << endl
                 << "Options:" << endl
                 << "  -h,--help \t \t"
                 << "Print this help message and exit" << endl
                 << "  -d,--deposits INT=5 \t"
                 << "Count of deposits" << endl;
            exit(EXIT_SUCCESS);
        }else{
            size_t pos; 
            //trying to convert string to int
            try{
                stoi(parameter, &pos);
            }catch(...){
                cerr << "Could not convert: balance = " + parameter << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }
            if(pos == parameter.length()){
                balance = stoi(parameter);
            }else{
                cerr << "Could not convert: balance = " + parameter << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }
        }
    }else if(argc == 3){
        string parameter1 = argv[1];
        string parameter2 = argv[2];
        string delimiter = "=";
        if(parameter1.substr(0, parameter1.find(delimiter)) == "--deposits"){
            string amountOfDeposits = "";
            for(int i = 11; (unsigned)i < parameter1.length(); i++){
                amountOfDeposits += parameter1[i];
            }

            size_t pos;
            try{
                stoi(amountOfDeposits, &pos);
            }catch(...){
                cerr << "Could not convert: deposits = " + amountOfDeposits << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }
            if(pos == amountOfDeposits.length()){
                deposits = stoi(amountOfDeposits);
            }else{
                cerr << "Could not convert: deposits = " + amountOfDeposits << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }
        }else{
            cerr << "Run with --help for more information" << endl;
            //exit code 1
            exit(EXIT_FAILURE);
        }
        size_t pos;
        try{
            stoi(parameter2, &pos);
        }catch(...){
            cerr << "Could not convert: balance = " + parameter2 << endl
                 << "Run with --help for more information" << endl;
            //exit code 1
            exit(EXIT_FAILURE);
        }
        if(pos == parameter2.length()){
            balance = stoi(parameter2);
        }else{
            cerr << "Could not convert: balance = " + parameter2 << endl
                 << "Run with --help for more information" << endl;
            //exit code 1
            exit(EXIT_FAILURE);
        }
       
    }else if(argc == 4){
        string parameter1 = argv[1];
        string parameter2 = argv[2];
        string parameter3 = argv[3];
        if(parameter1 == "-d"){
            size_t pos;
            try{
                stoi(parameter2, &pos);
            }catch(...){
                cerr << "Could not convert: deposits = " + parameter2 << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }
            if(pos == parameter2.length()){
                deposits = stoi(parameter2);
            }else{
                cerr << "Could not convert: deposits = " + parameter2 << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }

            try{
                stoi(parameter3, &pos);
            }catch(...){
                cerr << "Could not convert: balacne = " + parameter3 << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }
            if(pos == parameter3.length()){
                balance = stoi(parameter3);
            }else{
                cerr << "Could not convert: balacne = " + parameter3 << endl
                     << "Run with --help for more information" << endl;
                //exit code 1
                exit(EXIT_FAILURE);
            }
        }else{
            cerr << "Run with --help for more information" << endl;
            //exit code 1
            exit(EXIT_FAILURE);
        }
    }

    Account myAccount(balance);
    Depositer depo1(ref(myAccount), deposits);
    Depositer depo2(ref(myAccount), deposits);

    thread t1{depo1};
    thread t2{depo2};

    t1.join();
    t2.join();

    cout << "my balance: " << myAccount.get_balance() << " Euros" << endl;
}