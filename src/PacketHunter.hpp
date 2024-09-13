#pragma once
#include "Graphics/Graphics.hpp"

enum class PacketHunterEnum {
    Graphics_Raylib
};

class PacketHunter {
    private:
        Graphics *grf;

        unsigned char InitRaylib();
    public:
        PacketHunter(const unsigned char GraphicsLib);
        ~PacketHunter();
        void Run();
};
