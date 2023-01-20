#include<string>

class Clock{
private:
    std::string name_;
    int hours_, minutes_, seconds_;
public:
    Clock(std::string name_):name_(name_){};
    Clock(std::string name_, int hours_, int minutes_, int seconds_)
    :name_(name_), hours_(hours_), minutes_(minutes_), seconds_(seconds_){}
    void operator()();
};