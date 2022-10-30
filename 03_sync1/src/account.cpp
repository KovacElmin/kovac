#include "account.h"

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
        balance -= amount;
        return true;
    }
    else
    {
        return false;
    }
}