#pragma once
#include "../Devices/Devices.hpp"
#include <string>
#include <vector>

typedef struct guiElement {
    std::string Name;
    Color _Color;
    unsigned char Type;
    unsigned short Key;
} guiElement;

class PacketHunterGui {
    private:
        unsigned char Type = 0;
        float Scale;
        std::vector<guiElement> GuiElements;

        Devices *Devs;
    public:
        PacketHunterGui(Devices *Devs, float Scale);

        void Draw();
        void Update();

        void PushElement(guiElement *Element);
        void EraseElement(std::string Name);
};
