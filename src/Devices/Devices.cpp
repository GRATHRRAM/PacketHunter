#include "Devices.hpp"

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
