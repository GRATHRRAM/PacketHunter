#include "Devices.hpp"
#include <cstdlib>
#include <raylib.h>
#include <stdlib.h>

#define SQ (Vector2){static_cast<float>(10.f),static_cast<float>(10.f)}

Devices::Devices(float _Scale) {Scale = _Scale;}

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
    dev.Position.x = Position.x - Scale / 2;
    dev.Position.y = Position.y - Scale / 2;

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

std::string Type2String(unsigned char Type) {
    if(Type == (unsigned char) dvTypes::buffer)   return "Buffer";
    if(Type == (unsigned char) dvTypes::computer) return "Computer";
    if(Type == (unsigned char) dvTypes::hub)      return "Hub";
    if(Type == (unsigned char) dvTypes::cable)    return "Cable";

    return "\0";
}

Color Type2Color(unsigned char Type) {
    if(Type == (unsigned char) dvTypes::buffer)   return WHITE;
    if(Type == (unsigned char) dvTypes::computer) return DARKGRAY;
    if(Type == (unsigned char) dvTypes::hub)      return RED;
    if(Type == (unsigned char) dvTypes::cable)    return BLUE;
    return BLACK;
}

void Devices::DrawDevices() { /*TODO Textures*/
    for(unsigned long i=0; i < _Devices.size(); ++i) {
        DrawRectangle(_Devices[i].Position.x,
            _Devices[i].Position.y,
            Scale,
            Scale,
            Type2Color(_Devices[i].Type)
        );
        
        DrawText(Type2String(_Devices[i].Type).c_str(),
            _Devices[i].Position.x + Scale / 4,
            _Devices[i].Position.y + Scale / 4,
            Scale / 10,
            BLACK
        );
    }
}
