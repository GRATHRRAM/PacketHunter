#include "PacketHunter.hpp"
#include "Devices/Devices.hpp"
#include <cstdio>
#include <cstdlib>
#include <raylib.h>

PacketHunter::PacketHunter() {
    devs = new Devices();

    _Camera.zoom = 1.f;
    _Camera.target = {0, 0};
    _Camera.rotation = 0;
    
    InitWindow(1024, 576, "PacketHunter");
}

PacketHunter::~PacketHunter() {
    CloseWindow();
    delete devs;
}

void PacketHunter::Draw() {
    _Camera.offset = (Vector2){
        static_cast<float>(GetRenderWidth()  / 2.f),
        static_cast<float>(GetRenderHeight() / 2.f)
    };
    
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    BeginMode2D(_Camera);
        
    devs->DrawCables();
    devs->DrawDevices();
    
    EndMode2D();
    DrawFPS(10,10);
    EndDrawing();
}

void PacketHunter::Run() {
    Draw();
}
