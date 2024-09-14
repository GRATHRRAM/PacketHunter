#pragma once
#include <raylib.h>
#include <vector>
#include <string>

#define UINT32MAX 4294967295;
#define UINT48MAX 281474976710656;

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
    cable,
    buffer,
    computer,
    hub
};

class Devices {
    private:
    float Scale;
    
    unsigned long FindDevice(unsigned long ID);
    public:
    std::vector<dvLine>   _Cables;
    std::vector<dvDevice> _Devices;
    Devices(float Scale);

    void ConnectDevice(dvDevice *FirstDevice, dvDevice *SecondDevice);
    void DisconnectDevice(dvDevice *FirstDevice, dvDevice *SecondDevice);

    void AddDevice(unsigned char Type, Vector2 Position, std::string Name, std::string IP);
    void RemoveDevice(unsigned long ID);

    void DrawCables();
    void DrawDevices();

    float GetScale() {return Scale;}
};
