#include "Devices.hpp"
#include <cstdlib>
#include <raylib.h>
#include <stdlib.h>

#define SQ (Vector2){static_cast<float>(10.f),static_cast<float>(10.f)}

unsigned long Devices::FindDevice(unsigned long ID) {
    for(unsigned long i=0; i < _Devices.size(); ++i)
        if(ID == _Devices.at(i).ID) return i;
    return UINT32MAX;
}

void Devices::ConnectDevice(dvDevice *fdev, dvDevice *sdev) {
    dvLine line;
    line.FirstObjID    = fdev->ID;
    line.FirstObjType  = fdev->Type;
    line.SecondObjID   = sdev->ID;
    line.SecondObjType = sdev->Type;
    line._Color = (Color) {
        static_cast<unsigned char>(rand() % 255),
        static_cast<unsigned char>(rand() % 255),
        static_cast<unsigned char>(rand() % 255),
        255
    };

    _Cables.push_back(line);
}

void Devices::DisconnectDevice(dvDevice *fdev, dvDevice *sdev) {
    for(unsigned long i=0; i < _Cables.size(); ++i) {
        if (fdev->ID == _Cables.at(i).FirstObjID &&
            sdev->ID == _Cables.at(i).SecondObjID) {
            _Cables.erase(_Cables.begin() + i);
        }
    }
}

void Devices::AddDevice(unsigned char Type, Vector2 Position, std::string Name, std::string IP) {
    dvDevice dev;
    dev.ID   = rand() % UINT32MAX;
    dev.MAC  = rand() % 281474976710656;
    dev.Type = Type;
    dev.IP   = IP;
    dev.Name = Name;
    dev.Position = Position;

    _Devices.push_back(dev);
}

void Devices::RemoveDevice(unsigned long ID) {
   _Devices.erase(_Devices.begin() + FindDevice(ID)); 
}

void Devices::DrawCables() {
    for(unsigned long i=0; i < _Cables.size(); ++i) {
        DrawLineV(
                _Devices.at(FindDevice(_Cables.at(i).FirstObjID)).Position,
                _Devices.at(FindDevice(_Cables.at(i).FirstObjID)).Position,
                _Cables.at(i)._Color
        );
    }
}

void Devices::DrawDevices() {
    //White > buffer
    //Black > Computer
    //Red   > hub

    for(unsigned long i=0; i < _Devices.size(); ++i) {
        if(_Devices.at(i).Type == (unsigned char) dvTypes::buffer)   DrawRectangleV(_Devices.at(i).Position, SQ, WHITE);
        if(_Devices.at(i).Type == (unsigned char) dvTypes::computer) DrawRectangleV(_Devices.at(i).Position, SQ, BLACK);
        if(_Devices.at(i).Type == (unsigned char) dvTypes::hub)      DrawRectangleV(_Devices.at(i).Position, SQ, RED);
    }
}
