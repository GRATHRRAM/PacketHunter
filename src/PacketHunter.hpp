#pragma once
#include "Devices/Devices.hpp"
#include "Gui/PacketHunterGui.hpp"
#include <raylib.h>

class PacketHunter {
    private:
        Camera2D _Camera;
        Vector2 CameraTarget;
        float DeltaTime;

        Devices *devs;
        PacketHunterGui *gui;

        void MoveCamera();

        void Draw();
        void Event();
        void UpdateCamera();
        void Place(unsigned char Type);

    public:
        PacketHunter();
        ~PacketHunter();
        void Run();
};
