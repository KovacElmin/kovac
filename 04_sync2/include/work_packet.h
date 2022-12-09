#pragma once

class Work_Packet{
private:
    int id;
public:
    Work_Packet(int id):id(id){};
    const int getId(){return id;};
};