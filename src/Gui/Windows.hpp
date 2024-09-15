/*NOTE: This Is In Game Window Api Not For OS Windows*/
#pragma once
#include <raylib.h>
#include <string>
#include <vector>

namespace WindowLayout {
    /*Struct Layout*/
    //Rect/Vector2
    //WindowText
    //bool Values
    //Last bool is outline!
    //Colors

    typedef struct WindowText {
        Vector2 Position;
        std::string Text;
        unsigned char FontSize;
        Color Color;
    } WindowText;
    
    typedef struct WindowButton {
        Rectangle Button;
        WindowText Text;
        bool Pressed;
        bool OutLine;
        Color NotPressedColor;
        Color PressedColor;
    } WindowButton;

    typedef struct WindowInput {
        Rectangle InputRect;
        WindowText Text;
        bool Focus;
        bool Outline;
        Color TextColor;
        Color BackGround;
    } WindowInput;

    typedef struct WindowElement {
        Rectangle Element;
        bool Outline;
        Color Background;
        std::vector<WindowText>   Texts;
        std::vector<WindowButton> Buttons;
        std::vector<WindowInput>  Inputs;
    } WindowElement;
    
    extern WindowText ExempleText;
    extern WindowButton ExempleButton;
    extern WindowInput ExempleInput;
}

class Window {
    public:
    Rectangle _Window;
    std::string Title;
    Color TopBar;
    Color Background;
    bool OutLine;

    std::vector<WindowLayout::WindowElement> Elements;
    
    Window(Rectangle *Window, std::string Title);
    void UpdateWindow();
    void Draw();
};

class WindowManager {
    public:
    std::vector<Window> Windows;
    void PushWindow();
    void RemoveWindow();
    void UpdateWindows();
    void DrawWindows();
};
