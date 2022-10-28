#include "account.h"

class Account{

private:
    int balance;

public:
    Account(int balance){
        this->balance = balance;
    }

    int get_balance(){
        return balance;
    }

    void deposit(int amount){
        balance += amount;
    }

    bool withdraw(int amount){
        if(balance - amount >= 0){
            balance -= amount;
            return true;
        }else{
            return false;
        }
    }
};