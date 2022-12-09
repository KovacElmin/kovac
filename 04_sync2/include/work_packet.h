#pragma once

class WorkPacket{
private:
    int id;
public:
    WorkPacket(int id):id(id){};
    int getId() const{ return id; };
};