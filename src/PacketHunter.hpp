#pragma once
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
