#ifndef eWindow
#define eWindow

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>
#include <iostream>
#include <vector>
#include <functional>
#include "entity.hpp"

class Window {
    using callback = std::function<void()>;
    public:
        Window(std::string title, int width, int height, SDL_WindowFlags flags);
        ~Window();
    
    public:
        void render();
        void manageEvents();
        void run();
        SDL_Renderer* getRenderer();
        SDL_Window* getWindow();
        void setLogicalResolution(float w, float h, SDL_RendererLogicalPresentation presentation);
        void setRenderCallback(callback cb);
        void setLogicalLoop(callback ll);
        void setEventLoop(callback el);
        void setRunning(bool running);
    
    public:
        double deltaTime;
    
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Event event;
        callback renderCallback;
        callback logicalLoop;
        callback eventLoop;
    
    private:
        int width;
        int height;
        SDL_WindowFlags flags;
        std::string title;
        bool running;

};

#endif