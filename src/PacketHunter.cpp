#include "PacketHunter.hpp"
#include <cstdio>
#include <cstdlib>

PacketHunter::PacketHunter(const unsigned char GraphicsLib) {
    grf = new Graphics(GraphicsLib);
    grf->Init();
}

PacketHunter::~PacketHunter() {
    grf->Deinit();
}

void PacketHunter::Run() {

}
