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

#endif