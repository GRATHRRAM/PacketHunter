#include "Windows.hpp"
#include <raylib.h>
#include <string>


WindowLayout::WindowText WindowLayout::ExempleText = {
    (Vector2){0,0},
    "Text",
    2,
    BLACK
};

WindowLayout::WindowButton WindowLayout::ExempleButton = {
    (Rectangle){0,20,100,100},
    WindowLayout::ExempleText,
    false,
    true,
    LIGHTGRAY,
    DARKGRAY,
};

WindowLayout::WindowInput WindowLayout::ExempleInput = {
    (Rectangle){0, 140, 100, 100},
    WindowLayout::ExempleText,
    false,
    true,
    BLACK,
    LIGHTGRAY,
};

Window::Window(Rectangle *Window, std::string _Title) {
    _Window=*Window;
    Title=_Title;
    TopBar = GRAY;
    Background = LIGHTGRAY;
    OutLine = false;
}

void Window::UpdateWindow() {

}

void Window::Draw() {
    DrawRectangleRec(_Window, Background);
    DrawRectangle(_Window.x,_Window.y,_Window.width,10,TopBar);
}
