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
    DARKGRAY,
    LIGHTGRAY
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
    //Main Window
    DrawRectangleRec(_Window, Background);
    DrawRectangle(_Window.x,_Window.y,_Window.width,10,TopBar);

    //Elements
    for(unsigned int i=0; i < Elements.size(); ++i) {
        //Element
        if(Elements[i].Outline) DrawRectangleLinesEx(Elements[i].Element, 5, BLACK);
        
        //Text
        for(unsigned int ii=0; ii < Elements[i].Texts.size(); ++ii) {
            DrawText(
                Elements[i].Texts[ii].Text.c_str(),
                Elements[i].Texts[ii].Position.x,
                Elements[i].Texts[ii].Position.y,
                Elements[i].Texts[ii].FontSize,
                Elements[i].Texts[ii].Color
            );
        }

        //buttons
        for(unsigned int ii=0; ii < Elements[i].Buttons.size(); ++ii) {
            if(Elements[i].Buttons[ii].OutLine) DrawRectangleLinesEx(Elements[i].Buttons[ii].Button, 5, BLACK);
            
            if(Elements[i].Buttons[ii].Pressed) {
                DrawRectangleRec(
                    Elements[i].Buttons[ii].Button,
                    Elements[i].Buttons[ii].PressedColor
                );
            } else {
                DrawRectangleRec(
                    Elements[i].Buttons[ii].Button,
                    Elements[i].Buttons[ii].NotPressedColor
                );
            }
            
            DrawText(
                Elements[i].Buttons[ii].Text.Text.c_str(),
                Elements[i].Buttons[ii].Text.Position.x,
                Elements[i].Buttons[ii].Text.Position.y,
                Elements[i].Buttons[ii].Text.FontSize,
                Elements[i].Buttons[ii].Text.Color
            );
        }

        //Inputs
        for(unsigned int ii=0; ii < Elements[i].Inputs.size(); ++ii) {
            if(Elements[i].Inputs[ii].OutLine) DrawRectangleLinesEx(Elements[i].Inputs[ii].InputRect, 5, BLACK);
            
            if(Elements[i].Inputs[ii].Focus) {
                DrawRectangleRec(
                    Elements[i].Inputs[ii].InputRect,
                    Elements[i].Inputs[ii].FocusedBackground
                );           
            } else {
                DrawRectangleRec(
                    Elements[i].Inputs[ii].InputRect,
                    Elements[i].Inputs[ii].UnFocusedBackground
                );           
            }
            DrawText(
                Elements[i].Inputs[ii].Text.Text.c_str(),
                Elements[i].Inputs[ii].Text.Position.x,
                Elements[i].Inputs[ii].Text.Position.y,
                Elements[i].Inputs[ii].Text.FontSize,
                Elements[i].Inputs[ii].Text.Color
            );
        }
    }
}
