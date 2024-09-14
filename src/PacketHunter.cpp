#include "PacketHunter.hpp"
#include "Devices/Devices.hpp"
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include <string>
#include "raymath.h"

PacketHunter::PacketHunter() {
    devs = new Devices(50.f);
    gui = new PacketHunterGui(10.f);

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

void PacketHunter::Place(unsigned char Type) {
    if(Type == (unsigned char) dvTypes::cable) {
        //TODO Window api
    }
    if(Type == (unsigned char) dvTypes::buffer) {
        Vector2 m = GetMousePosition();
        m.x += CameraTarget.x - _Camera.offset.x;
        m.y += CameraTarget.y - _Camera.offset.y;

        devs->AddDevice(Type, m, "buffer" + std::to_string(rand()), "192.168.0." + std::to_string(rand() % 255));
    }
}

void PacketHunter::Draw() {
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
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Place(gui->GetType());
}

void PacketHunter::UpdateCamera() {    
    _Camera.target.x = Lerp(_Camera.target.x,CameraTarget.x, 0.1);
    _Camera.target.y = Lerp(_Camera.target.y,CameraTarget.y, 0.1);
    
    _Camera.offset = (Vector2){
        static_cast<float>(GetRenderWidth()  / 2.f),
        static_cast<float>(GetRenderHeight() / 2.f)
    };
}

void PacketHunter::Run() {
    while(!WindowShouldClose()) {
        DeltaTime = GetFrameTime();
        UpdateCamera();
        Event();
        gui->Update();
        Draw();
    }
}
