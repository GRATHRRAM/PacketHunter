#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include "Devices/Devices.hpp"

enum class PacketHunterEnum {
    Renderer_Raylib
};

class PacketHunter {
    public:
        PacketHunter(const unsigned char Renderer);
        ~PacketHunter();
        void Run();
};
