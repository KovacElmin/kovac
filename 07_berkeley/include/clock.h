#include <string>
#include <tuple>
#include <chrono>

class Clock{
private:
    std::string name_;
    int hours_, minutes_, seconds_;
    std::chrono::time_point<std::chrono::system_clock> editedTime;
public:
    Clock(std::string name_):name_(name_){};
    Clock(std::string name_, int hours_, int minutes_, int seconds_)
    : name_(name_), hours_(hours_), minutes_(minutes_), seconds_(seconds_){};
    void operator()();
    void set_time(int hours_, int minutes_, int seconds);
    std::tuple<int, int, int> get_time();
    long to_time();
    void from_time(long time);
};