#include "Windows.hpp"
#include <cstdio>
#include <raylib.h>
#include <string>

Window::Window(std::string _Title, unsigned short _TopBarSize, Rectangle *Window) {
    _Window=*Window;
    Title=_Title;
    TopBar = GRAY;
    Background = LIGHTGRAY;
    OutLine = true;
    DestroyWindow = false;
    TopBarSize = _TopBarSize;
}

void Window::UpdateWindow() {
    Vector2 m = GetMousePosition();

    if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) Drag = false;
    
    if (CheckCollisionPointRec(m,_Window)) {
        //Window
        if(CheckCollisionPointRec(m, (Rectangle){_Window.x, _Window.y, _Window.width,(float) TopBarSize})) {
            //TopBar
            
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !Drag) {
                if(CheckCollisionPointRec(m, (Rectangle){
                            _Window.x + _Window.width - TopBarSize,
                            _Window.y, _Window.width,(float) TopBarSize})) DestroyWindow = true;
            
                Drag = true;
                Dist.x = m.x - _Window.x;
                Dist.y = m.y - _Window.y;
            }   
        } 
    }

        if(Drag) goto UpdateWindowEnd;
        
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
                
                if(IsKeyPressed(KEY_ENTER)) { 
                    if (!IsKeyDown(KEY_LEFT_SHIFT)) {
                        Elements[i].Inputs[ii].Focus = false;
                        Elements[i].Inputs[ii].Text.Text = WrapText(
                        Elements[i].Inputs[ii].Text.Text,
                        Elements[i].Inputs[ii].Text.TextRect.width - Elements[i].Inputs[ii].Text.TextRect.x,
                        Elements[i].Inputs[ii].Text.FontSize);
                    } else {
                        Elements[i].Inputs[ii].Text.Text.push_back('\n');
                    }
                }  

                if(Elements[i].Inputs[ii].Focus) {
                    char key = GetCharPressed(); 
                    const unsigned short MaxChars = 2048;
                    
                    if (IsKeyPressed(KEY_DELETE)) Elements[i].Inputs[ii].Text.Text = "";
                    else if(IsKeyPressed(KEY_BACKSPACE) && !Elements[i].Inputs[ii].Text.Text.empty()) Elements[i].Inputs[ii].Text.Text.pop_back();
                    else if(key > 0 && Elements[i].Inputs[ii].Text.Text.size() < MaxChars + 1) Elements[i].Inputs[ii].Text.Text += key;
                   
                    if(!IsCursorHidden()) DisableCursor();
                } else if(IsCursorHidden()) {
                    EnableCursor();
                }
            }
        }
    
    UpdateWindowEnd:;
    if(Drag) {_Window.x = m.x - Dist.x; _Window.y = m.y - Dist.y;}
}

void Window::Draw() {
    //Main Window
    DrawRectangleRec(_Window, Background);
    DrawText(Title.c_str(),_Window.x + 5, _Window.y + 2 , 2, BLACK);
    
    if(OutLine) DrawRectangleLinesEx(_Window, 10, BLACK);    

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
                Elements[i].Texts[ii].TextRect.x + LocalElementPos.x,
                Elements[i].Texts[ii].TextRect.y + LocalElementPos.y,
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
                Elements[i].Buttons[ii].Text.TextRect.x + LocalButtonPos.x,
                Elements[i].Buttons[ii].Text.TextRect.y + LocalButtonPos.y,
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
            DrawText(
                Elements[i].Inputs[ii].Text.Text.c_str(),
                Elements[i].Inputs[ii].Text.TextRect.x + LocalInputPos.x,
                Elements[i].Inputs[ii].Text.TextRect.y + LocalInputPos.y,
                Elements[i].Inputs[ii].Text.FontSize,
                Elements[i].Inputs[ii].Text.TextColor
            );
        }

        //TopBar
        DrawRectangle(_Window.x,_Window.y,_Window.width,TopBarSize,TopBar);
        //Window Title
        DrawText(Title.c_str(),_Window.x + 5, _Window.y + 2, 3, BLACK);
        
        //Red Squer on The window
        DrawRectangle(
            _Window.x + _Window.width - TopBarSize,
            _Window.y,
            TopBarSize,
            TopBarSize,
            RED
        );
        DrawRectangleLinesEx( (Rectangle) {
            _Window.x + _Window.width - TopBarSize,
            _Window.y,
            (float) TopBarSize,
            (float) TopBarSize},
            2,
            BLACK
        );
    }
}

void Window::SetCamera(Camera2D *Cam) {
    _Camera = Cam;
}

std::string Window::WrapText(const std::string& text, const unsigned int maxWidth, const unsigned int fontSize) {
    std::vector<std::string> wrappedLines;
    std::string currentLine;
    unsigned int currentLineWidth = 0;
    
    for (size_t i = 0; i < text.size(); ++i) {
        char ch = text[i];
        std::string newLine = currentLine + ch;
        int lineWidth = MeasureText(newLine.c_str(), fontSize);
        
        if (ch == ' ' || ch == '\n') {
            if (lineWidth > maxWidth) {
                wrappedLines.push_back(currentLine);
                currentLine.clear();
                currentLineWidth = 0;
            }
            if (ch == '\n') {
                if (!currentLine.empty()) {
                    wrappedLines.push_back(currentLine);
                    currentLine.clear();
                }
                continue;
            }
        }
        
        if (lineWidth > maxWidth) {
            wrappedLines.push_back(currentLine);
            currentLine.clear();
            currentLineWidth = 0;
            // Add the character to the new line
            currentLine += ch;
        } else {
            currentLine += ch;
        }
    }
    
    if (!currentLine.empty()) {
        wrappedLines.push_back(currentLine);
    }
    
    std::string wrappedstring  = "";
    
    for(unsigned int i=0; i < wrappedLines.size(); ++i) {
        wrappedstring += wrappedLines[i] + '\n';
    }

    return wrappedstring;
}
