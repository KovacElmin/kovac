#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <mutex>

class Account{

private:
    int balance;
    //mutex for synchronisation
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
    int deposits;
public:
    Depositer(Account& acc, int depos):account(acc), deposits(depos){};
    void operator()(){
        for(int i = 0; i < deposits; i++){
            account.deposit(1);
        }
    };
    

};

#endif