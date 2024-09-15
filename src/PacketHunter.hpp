#pragma once
#include "Devices/Devices.hpp"
#include "Gui/PacketHunterGui.hpp"
#include "Gui/Windows.hpp"
#include <raylib.h>

class PacketHunter {
    private:
        Camera2D _Camera;
        Vector2 CameraTarget;
        float DeltaTime;

        Devices *devs;
        PacketHunterGui *gui;
        WindowManager *winman;

        void MoveCamera();

        void Draw();
        void Event();
        void UpdateCamera();
        void Place(unsigned char Type);
        void Remove();
        Vector2 CalculateCursorPosition();
    public:
        PacketHunter();
        ~PacketHunter();
        void Run();
};
