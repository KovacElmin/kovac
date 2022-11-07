#include <iostream>
#include <thread>
#include "account.h"

using namespace std;

int main(){
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
    Account myAccount(0);
    Depositer depo1(ref(myAccount));
    Depositer depo2(ref(myAccount));

    thread t1{depo1};
    thread t2{depo2};

    t1.join();
    t2.join();

    cout << myAccount.get_balance();
}