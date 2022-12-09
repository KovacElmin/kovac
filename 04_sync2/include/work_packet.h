#pragma once

class WorkPacket{
private:
    int id;
public:
    WorkPacket(int id):id(id){};
    const int getId(){return id;};
};