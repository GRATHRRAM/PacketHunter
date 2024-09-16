#include "Windows.hpp"
#include <raylib.h>

WindowManager::WindowManager(float b, Camera2D *Cam) {WindowsYBorderUP = b; _Camera = Cam;}

bool WindowManager::CheckWindowsColision() {
    Vector2 m = GetMousePosition();
   
    for(unsigned int i=0; i < Windows.size(); ++i) {
        if(CheckCollisionRecs((Rectangle){m.x,m.y,1,1}, Windows[i]._Window)) {
            return true;
        }
    }
    return false;
}

void WindowManager::PushWindow(Window *Window) {
    if(Window->_Window.y < WindowsYBorderUP) Window->_Window.y = WindowsYBorderUP;
    Window->SetCamera(_Camera);
    Windows.push_back(*Window);
}

void WindowManager::DrawWindows() {
    for(unsigned int i=0; i < Windows.size(); ++i) Windows[i].Draw();
}

void WindowManager::UpdateWindows() {
    for(unsigned int i=0; i < Windows.size(); ++i) {
        if(Windows[i].DestroyWindow) Windows.erase(Windows.begin() + i); 
        Windows[i].UpdateWindow();
    }
}
