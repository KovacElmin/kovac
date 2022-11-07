#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <mutex>

class Account{

private:
    int balance;
    std::mutex m;

public:
    Account(int balance);
    int get_balance();
    void deposit(int amount);
    bool withdraw(int amount);

};

class Depositer{
private:
    Account& account;
public:
    Depositer(Account& acc):account(acc){};
    void operator()(){
        for(int i = 0; i < 5; i++){
            account.deposit(1);
        }
    };

};

#endif