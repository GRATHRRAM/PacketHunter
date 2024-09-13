#include "PacketHunter.hpp"
#include <cstdio>
#include <cstdlib>

PacketHunter::PacketHunter(const unsigned char _Renderer) {
    rnd = new Renderer(_Renderer);
    rnd->Init();
}

PacketHunter::~PacketHunter() {
    rnd->Deinit();
}

void PacketHunter::Run() {

}
