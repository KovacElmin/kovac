#include <iostream>
#include "account.h"

using namespace std;

int main(){
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
    
}