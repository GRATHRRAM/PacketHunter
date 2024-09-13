#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#define UINT32MAX 4294967295;

typedef struct dvLine {
    unsigned long FirstObjID;
    unsigned char FirstObjType;
    unsigned long SecondObjID;
    unsigned char SecondObjType;
    Color _Color;
} phLine;

typedef struct dvDevice {
    unsigned long ID;
    unsigned char Type;
    Vector2 Position;
    std::string Name;
    std::string IP;
    std::string MAC;
} phDevice;

enum class dvTypes {
    buffer,
    computer,
    hub
};

class Devices {
    private:
    std::vector<dvLine>   _Cables;
    std::vector<dvDevice> _Devices;
    
    unsigned long FindDevice(unsigned long ID);
    public:

    void ConnectDevice(dvDevice *FirstDevice, dvDevice *SecondDevice);
    void DisconnectDevice(dvDevice *FirstDevice, dvDevice *SecondDevice);

    void AddDevie(unsigned char Type, Vector2 Position, std::string Name, std::string IP);
    void RemoveDevide(unsigned long ID);

    void DrawCables();
    void DrawDevices();

};
