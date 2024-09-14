#include "PacketHunterGui.hpp"
#include <raylib.h>

PacketHunterGui::PacketHunterGui(float _Scale) {Scale = _Scale;}

void PacketHunterGui::Draw() {
    float x = 0;
    float div = (float) GetRenderWidth() / GuiElements.size();

    for(unsigned int i=0; i < GuiElements.size(); ++i) {
        if(Type == GuiElements[i].Type) {
            DrawRectangle(x, 0, div, 7 * Scale, GuiElements[i]._Color);
            DrawText(GuiElements[i].Name.c_str(), x + div / 2, 0, 2 * Scale, BLACK);
        } else {
            DrawRectangle(x, 0, div, 5 * Scale, GuiElements[i]._Color);
            DrawText(GuiElements[i].Name.c_str(), x + div / 2, 0, 2 * Scale, BLACK);
        }
        x += div;
    }
}

void PacketHunterGui::Update() {
    for(unsigned int i=0; i < GuiElements.size(); ++i) 
        if(IsKeyPressed(GuiElements[i].Key)) Type = GuiElements[i].Type;
}

void PacketHunterGui::PushElement(guiElement *Element) {
    GuiElements.push_back(*Element);
}

void PacketHunterGui::EraseElement(std::string name) {
    for(unsigned int i=0; i < GuiElements.size(); ++i) {
        if(GuiElements[i].Name == name) GuiElements.erase(GuiElements.begin() + i);
    }
}

unsigned char PacketHunterGui::GetType() {
    return Type;
}
