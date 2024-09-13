#pragma once
#include "Devices/Devices.hpp"
#include <raylib.h>

class PacketHunter {
    private:
        Camera2D _Camera;
        Devices *devs;

        void Draw();

    public:
        PacketHunter();
        ~PacketHunter();
        void Run();
};
