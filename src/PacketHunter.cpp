#include "PacketHunter.hpp"
#include "Devices/Devices.hpp"
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include "raymath.h"

PacketHunter::PacketHunter() {
    devs = new Devices();
    gui = new PacketHunterGui(devs, 10.f);

    guiElement Cable;
    Cable.Name = "Cable";
    Cable.Key  = KEY_ONE;
    Cable.Type = (unsigned char) dvTypes::cable;
    Cable._Color = BLUE;

    guiElement Buffer;
    Buffer.Name = "Buffer";
    Buffer.Key  = KEY_TWO;
    Buffer.Type = (unsigned char) dvTypes::buffer;
    Buffer._Color = RED;

    gui->PushElement(&Cable);
    gui->PushElement(&Buffer);
   
    _Camera.zoom = 1.f;
    _Camera.target = {0, 0};
    _Camera.rotation = 0;
    CameraTarget = {0,0};
    
    InitWindow(1024, 576, "PacketHunter");
    SetTargetFPS(60);
    
    _Camera.offset = (Vector2){
        static_cast<float>(GetRenderWidth()  / 2.f),
        static_cast<float>(GetRenderHeight() / 2.f)
    };
}

PacketHunter::~PacketHunter() {
    CloseWindow();
    delete devs;
    delete gui;
}

void PacketHunter::MoveCamera() {
    if(IsKeyDown(KEY_UP))    CameraTarget.y -= 50.0f * DeltaTime;
    if(IsKeyDown(KEY_DOWN))  CameraTarget.y += 50.0f * DeltaTime;
    if(IsKeyDown(KEY_LEFT))  CameraTarget.x -= 50.0f * DeltaTime;
    if(IsKeyDown(KEY_RIGHT)) CameraTarget.x += 50.0f * DeltaTime;
}

void PacketHunter::Draw() {
    _Camera.target.x = Lerp(_Camera.target.x,CameraTarget.x, 0.1);
    _Camera.target.y = Lerp(_Camera.target.y,CameraTarget.y, 0.1);
    
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    BeginMode2D(_Camera);
    
    DrawRectangle(0,0,10,10,RED);

    devs->DrawCables();
    devs->DrawDevices();
    
    EndMode2D();
    
    gui->Draw();

    EndDrawing();
}

void PacketHunter::Event() {
    MoveCamera();
}

void PacketHunter::Run() {
    while(!WindowShouldClose()) {
        DeltaTime = GetFrameTime();
        Event();
        gui->Update();
        Draw();
    }
}
