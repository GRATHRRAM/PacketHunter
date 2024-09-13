#include "Renderer.hpp"
#include "../PacketHunter.hpp"
#include <raylib.h>

#ifdef DEBUG
#include <cassert>
#endif // DEBUG

Renderer::Renderer(const unsigned char rr) {
    _Renderer = rr;
    Inited = 0;
    Init();
}

Renderer::~Renderer() {
    Deinit();
}

void Renderer::Init() {
    #ifdef DEBUG
        assert (Inited); //Deinit() First Bozo
    #endif // DEBUG
    if(Inited) return;
    
    if(_Renderer == (unsigned char) PacketHunterEnum::Renderer_Raylib) {
        InitWindow(1024, 576, "PacketHunter -- Raylib");
        Inited = 1;
        return;
    }
}

void Renderer::Deinit() {
    #ifdef DEBUG
        assert (!Inited); //Init() First Bozo
    #endif // DEBUG
    if(!Inited) return;

    if(_Renderer == (unsigned char) PacketHunterEnum::Renderer_Raylib) {
        CloseWindow();
        Inited = 0;
        return;
    }
}
