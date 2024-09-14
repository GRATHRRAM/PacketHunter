#include "PacketHunterGui.hpp"
#include <raylib.h>

PacketHunterGui::PacketHunterGui(Devices *_Devs, float _Scale) {
    Devs = _Devs;
    Scale = _Scale;
}

void PacketHunterGui::Draw() {
    float x = 0;
    float div = (float) GetRenderWidth() / GuiElements.size();

    for(unsigned int i=0; i < GuiElements.size(); ++i) {
        if(Type == GuiElements[i].Type) {
            DrawRectangle(x, 0, div, 7 * Scale, GuiElements[i]._Color);
            DrawText(GuiElements[i].Name.c_str(), x, 0, 1 * Scale, BLACK);
        } else {
            DrawRectangle(x, 0, div, 5 * Scale, GuiElements[i]._Color);
            DrawText(GuiElements[i].Name.c_str(), x, 0, 1 * Scale, BLACK);
        }
        x += div;
    }
}

void PacketHunterGui::Update() {
    if(IsKeyPressed(KEY_ONE)) Type = (unsigned char) dvTypes::cable;
    if(IsKeyPressed(KEY_TWO)) Type = (unsigned char) dvTypes::buffer;
}

void PacketHunterGui::PushElement(guiElement *Element) {
    GuiElements.push_back(*Element);
}

void PacketHunterGui::EraseElement(std::string name) {
    for(unsigned int i=0; i < GuiElements.size(); ++i) {
        if(GuiElements[i].Name == name) GuiElements.erase(GuiElements.begin() + i);
    }
}
