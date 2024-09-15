#include "Windows.hpp"
#include <cstdio>
#include <raylib.h>
#include <string>


WindowLayout::WindowText WindowLayout::ExempleText = {
    (Vector2){10,10},
    "Text",
    2,
    BLACK
};

WindowLayout::WindowButton WindowLayout::ExempleButton = {
    (Rectangle){20,20,100,100},
    WindowLayout::ExempleText,
    false,
    true,
    DARKGRAY,
    LIGHTGRAY,
};

WindowLayout::WindowInput WindowLayout::ExempleInput = {
    (Rectangle){20, 140, 100, 100},
    WindowLayout::ExempleText,
    false,
    true,
    DARKGRAY,
    LIGHTGRAY,
};

Window::Window(std::string _Title, Rectangle *Window) {
    _Window=*Window;
    Title=_Title;
    TopBar = GRAY;
    Background = LIGHTGRAY;
    OutLine = false;
}

void Window::UpdateWindow() {
    Vector2 m = GetMousePosition();

    if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) Drag = false;
    
    if (CheckCollisionPointRec(m,_Window)) {
        //Window
        if(CheckCollisionPointRec(m, (Rectangle){_Window.x, _Window.y, _Window.width, 10})) {
            //TopBar
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !Drag) {
                Drag = true;
                Dist.x = m.x - _Window.x;
                Dist.y = m.y - _Window.y;
            }   
        } 

        //Elements
        for(unsigned int i=0; i < Elements.size(); ++i) {
            //Buttons
            for(unsigned int ii=0; ii < Elements[i].Buttons.size(); ++ii) {
                Vector2 GlobalPosition = {
                    _Window.x + Elements[i].Element.x + Elements[i].Buttons[ii].Button.x, 
                    _Window.y + Elements[i].Element.y + Elements[i].Buttons[ii].Button.y 
                };

                if(CheckCollisionPointRec(m,
                    (Rectangle) {
                    GlobalPosition.x,
                    GlobalPosition.y,
                    Elements[i].Buttons[ii].Button.width,
                    Elements[i].Buttons[ii].Button.height}) &&
                    IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    
                    Elements[i].Buttons[ii].Pressed = true;
                } else Elements[i].Buttons[ii].Pressed = false;
            }
            //Inputs

            for(unsigned int ii=0; ii < Elements[i].Inputs.size(); ++ii) {
                Vector2 GlobalPosition = {
                    _Window.x + Elements[i].Element.x + Elements[i].Inputs[ii].InputRect.x, 
                    _Window.y + Elements[i].Element.y + Elements[i].Inputs[ii].InputRect.y 
                };

                if(CheckCollisionPointRec(m,
                    (Rectangle) {
                    GlobalPosition.x,
                    GlobalPosition.y,
                    Elements[i].Inputs[ii].InputRect.width,
                    Elements[i].Inputs[ii].InputRect.height}) &&
                    IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    
                    Elements[i].Inputs[ii].Focus = true;
                } 
                
                if(IsKeyPressed(KEY_ENTER)) Elements[i].Inputs[ii].Focus = false;
                
                if(Elements[i].Inputs[ii].Focus) {
                    if(!IsCursorHidden()) DisableCursor();
                    if(IsKeyPressed(KEY_BACKSPACE)) Elements[i].Inputs[ii].Text.Text.pop_back();
                    else Elements[i].Inputs[ii].Text.Text += GetCharPressed();
                } else if(IsCursorHidden()) {
                    EnableCursor();
                }
            }
        }
    }

    if(Drag) {_Window.x = m.x - Dist.x; _Window.y = m.y - Dist.y;}
}

void Window::Draw() {
    //Main Window
    DrawRectangleRec(_Window, Background);
    DrawText(Title.c_str(),_Window.x + 5, _Window.y + 2 , 2, BLACK);


    //Elements
    for(unsigned int i=0; i < Elements.size(); ++i) {
        //Element
        Rectangle LocalElementPos = {
            _Window.x + Elements[i].Element.x,
            _Window.y + Elements[i].Element.y,
            Elements[i].Element.width,
            Elements[i].Element.height
        };

        if(Elements[i].Outline) DrawRectangleLinesEx(LocalElementPos, 2, BLACK);
        DrawRectangleRec(LocalElementPos, Elements[i].Background);
        
        //Text
        for(unsigned int ii=0; ii < Elements[i].Texts.size(); ++ii) {
            DrawText(
                Elements[i].Texts[ii].Text.c_str(),
                Elements[i].Texts[ii].Position.x + LocalElementPos.x,
                Elements[i].Texts[ii].Position.y + LocalElementPos.y,
                Elements[i].Texts[ii].FontSize,
                Elements[i].Texts[ii].TextColor
            );
        }

        //buttons
        for(unsigned int ii=0; ii < Elements[i].Buttons.size(); ++ii) {
            Rectangle LocalButtonPos = {
                LocalElementPos.x + Elements[i].Buttons[ii].Button.x,
                LocalElementPos.y + Elements[i].Buttons[ii].Button.y,
                Elements[i].Buttons[ii].Button.width,
                Elements[i].Buttons[ii].Button.height
            };

            if(Elements[i].Buttons[ii].OutLine) DrawRectangleLinesEx(LocalButtonPos, 2, BLACK);
            
            if(Elements[i].Buttons[ii].Pressed) {
                DrawRectangleRec(
                    LocalButtonPos,
                    Elements[i].Buttons[ii].PressedColor
                );
            } else {
                DrawRectangleRec(
                    LocalButtonPos,
                    Elements[i].Buttons[ii].NotPressedColor
                );
            }
            
            DrawText(
                Elements[i].Buttons[ii].Text.Text.c_str(),
                Elements[i].Buttons[ii].Text.Position.x + LocalButtonPos.x,
                Elements[i].Buttons[ii].Text.Position.y + LocalButtonPos.y,
                Elements[i].Buttons[ii].Text.FontSize,
                Elements[i].Buttons[ii].Text.TextColor
            );
        }

        //Inputs
        for(unsigned int ii=0; ii < Elements[i].Inputs.size(); ++ii) {
            Rectangle LocalInputPos = {
                LocalElementPos.x + Elements[i].Inputs[ii].InputRect.x,
                LocalElementPos.y + Elements[i].Inputs[ii].InputRect.y,
                Elements[i].Inputs[ii].InputRect.width,
                Elements[i].Inputs[ii].InputRect.height
            };
            
            if(Elements[i].Inputs[ii].Outline) DrawRectangleLinesEx(LocalInputPos, 2, BLACK);
            
            if(Elements[i].Inputs[ii].Focus) {
                DrawRectangleRec(
                    LocalInputPos,
                    Elements[i].Inputs[ii].FocusedBackground
                );           
            } else {
                DrawRectangleRec(
                    LocalInputPos,
                    Elements[i].Inputs[ii].UnFocusedBackground
                );           
            }
            //TODO TEXTBOX
            DrawText(
                Elements[i].Inputs[ii].Text.Text.c_str(),
                Elements[i].Inputs[ii].Text.Position.x + LocalInputPos.x,
                Elements[i].Inputs[ii].Text.Position.y + LocalInputPos.y,
                Elements[i].Inputs[ii].Text.FontSize,
                Elements[i].Inputs[ii].Text.TextColor
            );
        }

        //TopBar
        DrawRectangle(_Window.x,_Window.y,_Window.width,10,TopBar);
        //Window Title
        DrawText(Title.c_str(),_Window.x + 5, _Window.y, 2, BLACK);
    }
}

void Window::SetCamera(Camera2D *Cam) {
    _Camera = Cam;
}
