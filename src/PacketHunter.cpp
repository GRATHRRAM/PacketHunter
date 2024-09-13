#include "PacketHunter.hpp"
#include <cstdio>
#include <cstdlib>
#include <raylib.h>

PacketHunter::PacketHunter(const unsigned char _Renderer) {
    InitWindow(1024, 576, "PacketHunter");
}

PacketHunter::~PacketHunter() {
    CloseWindow();
}

void PacketHunter::Run() {

}
