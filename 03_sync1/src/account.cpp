#include "account.h"
#include <thread>

using namespace std;

Account::Account(int balance)
{
    this->balance = balance;
}

int Account::get_balance()
{
    return balance;
}

void Account::deposit(int amount)
{
    //unique lock for critical area
    unique_lock<mutex> unique(m);
    balance += amount;
}

bool Account::withdraw(int amount)
{
    //lock guard for critical area
    lock_guard<mutex> guard{m};   
    if (balance - amount >= 0)
    {
        this_thread::yield();
        balance -= amount;
        return true;
    }
    else
    {
        return false;
    }
}