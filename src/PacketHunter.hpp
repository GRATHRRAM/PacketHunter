#pragma once
#include "Devices/Devices.hpp"
#include <raylib.h>

class PacketHunter {
    private:
        Camera2D _Camera;
        Vector2 CameraTarget;
        Devices *devs;
        float DeltaTime;

        void MoveCamera();

        void Draw();
        void Event();

    public:
        PacketHunter();
        ~PacketHunter();
        void Run();
};
