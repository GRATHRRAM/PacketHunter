#pragma once
#include "Renderer/Renderer.hpp"

enum class PacketHunterEnum {
    Renderer_Raylib
};

class PacketHunter {
    private:
        Renderer *rnd;
    public:
        PacketHunter(const unsigned char Renderer);
        ~PacketHunter();
        void Run();
};
