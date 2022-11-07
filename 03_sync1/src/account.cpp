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
    int tmp{balance};
    std::this_thread::sleep_for(10ms);
    balance = tmp + amount;
}

bool Account::withdraw(int amount)
{
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