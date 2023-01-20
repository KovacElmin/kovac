#include<string>

class Clock{
private:
    std::string name_;
    int hours_, minutes_, seconds_;
public:
    Clock(std::string name_):name_(name_){};
    void operator()();
};