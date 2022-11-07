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
    balance += amount;
}

bool Account::withdraw(int amount)
{
    
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