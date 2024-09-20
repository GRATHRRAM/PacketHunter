#include "PacketHunter.hpp"
#include "Devices/Devices.hpp"
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include <string>
#include "Gui/Windows.hpp"
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

    winman = new WindowManager(gui->GetGuiYUpBorder(true), &_Camera);
    
    Rectangle rect = {200,200, 360, 240};
    Window win("Cool Window", 16, &rect);
    
    WindowLayout::WindowText txt = {0};
    txt.Text = "Text";
    txt.TextRect = (Rectangle){20,20,100,100};
    txt.FontSize = 4;
    txt.TextColor = BLACK;

    WindowLayout::WindowButton but = {0};
    but.Text = txt; but.Text.Text = "Button";
    but.Text.TextColor = BLUE;
    but.Button = (Rectangle){20,40,100,100};
    but.OutLine = true;
    but.PressedColor = RED;
    but.NotPressedColor = PURPLE;

    WindowLayout::WindowInput inp = {0};
    inp.Text = txt; inp.Text.Text = "Input";
    inp.Text.TextColor = GREEN; 
    inp.InputRect = (Rectangle){140, 40, 100, 100};
    inp.Text.TextRect = (Rectangle){10, 10, inp.InputRect.width - 10, inp.InputRect.height - 10};

    inp.Outline = true;
    inp.FocusedBackground = WHITE;
    inp.UnFocusedBackground = GRAY;

    WindowLayout::WindowElement el = {0};
    el.Element = {0,0,360,240};
    el.Outline = true;
    el.Background = (Color) { 170, 170, 170, 255 };

    el.Texts.push_back(txt);
    el.Buttons.push_back(but);
    el.Inputs.push_back(inp);

    win.Elements.push_back(el);

    winman->PushWindow(&win);
}

PacketHunter::~PacketHunter() {
    CloseWindow();
    delete devs;
    delete gui;
    delete winman;
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
        Vector2 m = CalculateCursorPosition();

        devs->AddDevice(Type, m, "buffer" + std::to_string(rand()), "192.168.0." + std::to_string(rand() % 255));
    }
}

void PacketHunter::Remove() {
    Vector2 m = PacketHunter::CalculateCursorPosition();
    for(unsigned int i=0; i < devs->_Devices.size(); ++i) {
        if(CheckCollisionPointRec(m,
            (Rectangle){
            devs->_Devices[i].Position.x,
            devs->_Devices[i].Position.y,
            devs->GetScale(),
            devs->GetScale()}
        )) {
            devs->_Devices.erase(devs->_Devices.begin() + i);
        }
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
   
    winman->DrawWindows();
    gui->Draw();

    EndDrawing();
}

void PacketHunter::Event() {
    MoveCamera();
    if(!winman->CheckWindowsColision()) { 
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Place(gui->GetType());
        if(IsKeyPressed(KEY_R)) Remove();
    }
    winman->UpdateWindows();
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

Vector2 PacketHunter::CalculateCursorPosition() {
    Vector2 m = GetMousePosition();
    m.x += CameraTarget.x - _Camera.offset.x;
    m.y += CameraTarget.y - _Camera.offset.y;
    return m;
}
