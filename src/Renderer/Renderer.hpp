#pragma once

class Renderer {
    private:
        unsigned char _Renderer;
        bool Inited;
    public:
        Renderer(const unsigned char Renderer);
        ~Renderer();

        void Init();
        void Deinit();

        /*Rendering Functions*/
};
