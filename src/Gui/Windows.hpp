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
        Color TextColor;
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
        Color UnFocusedBackground;
        Color FocusedBackground;
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
    private:
        Camera2D *_Camera;
        bool Drag;
    public:
    Rectangle _Window;
    std::string Title;
    Color TopBar;
    Color Background;
    bool OutLine;
    Vector2 Dist;

    std::vector<WindowLayout::WindowElement> Elements;
    
    Window(std::string Title, Rectangle *Window);
    void UpdateWindow();
    void Draw();
    void SetCamera(Camera2D *Camera);
};

class WindowManager {
    private:
        Camera2D *_Camera;
        Vector2 (*ccp)(void);
    public:
    float WindowsYBorderUP;
    WindowManager(float WindowsYBordedUP, Camera2D *Camera);

    std::vector<Window> Windows;
    bool CheckWindowsColision();
    void PushWindow(Window *Window);
    void UpdateWindows();
    void DrawWindows();
};
