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
    //OutlineSize 
    //Last bool is outline!
    //Colors

    typedef struct WindowText {
        Rectangle TextRect;
        std::string Text;
        unsigned char FontSize;
        Color TextColor;
    } WindowText;
    
    typedef struct WindowButton {
        Rectangle Button;
        WindowText Text;
        bool Pressed;
        bool Outline;
        unsigned char OutlineSize;
        Color NotPressedColor;
        Color PressedColor;
    } WindowButton;

    typedef struct WindowInput { 
        Rectangle InputRect;
        WindowText Text;
        bool Focus;
        bool Outline;
        unsigned char OutlineSize;
        Color UnFocusedBackground;
        Color FocusedBackground;
    } WindowInput;

    typedef struct WindowElement {
        Rectangle Element;
        bool Show;
        bool Outline;
        unsigned char OutlineSize;
        Color Background;
        std::vector<WindowText>   Texts;
        std::vector<WindowButton> Buttons;
        std::vector<WindowInput>  Inputs;
    } WindowElement;
}

class Window {
    private:
        Camera2D *_Camera;
        bool Drag;
        std::string WrapText(const std::string& text, unsigned int maxWidth, unsigned int fontSize);
    public:
    Rectangle _Window;
    std::string Title;
    Color TopBar;
    Color Background;
    bool OutLine;
    unsigned char OutlineSize;
    Vector2 Dist;
    bool DestroyWindow;
    unsigned short TopBarSize;

    std::vector<WindowLayout::WindowElement> Elements;
    
    Window(std::string Title, unsigned short TopBarSize, Rectangle *Window);
    void UpdateWindow();
    void Draw();
    void SetCamera(Camera2D *Camera);
};

class WindowManager {
    private:
        Camera2D *_Camera;
    public:
    float WindowsYBorderUP;
    WindowManager(float WindowsYBordedUP, Camera2D *Camera);

    std::vector<Window> Windows;
    bool CheckWindowsColision();
    void PushWindow(Window *Window);
    void UpdateWindows();
    void DrawWindows();
};
