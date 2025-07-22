#include "window.hpp"

//clock logic
    int now = SDL_GetPerformanceCounter();
    int last = 0;

Window::Window(std::string title, int width, int height, SDL_WindowFlags flags):
title(title),
width(width),
height(height),
flags(flags),
running(true)
{
    window = SDL_CreateWindow(title.c_str(), width, height, flags);
    renderer = SDL_CreateRenderer(window, "opengl");

    if(!window || !renderer){
        SDL_Log("Window initialization error: %s", SDL_GetError());
        SDL_Quit();
    }
}

Window::~Window(){
    if(window) SDL_DestroyWindow(window);
    if(renderer) SDL_DestroyRenderer(renderer);
}

void Window::render(){
    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime = (double)(now-last) / SDL_GetPerformanceFrequency();

    SDL_SetRenderDrawColor(renderer, 167, 199, 231, 255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

}

void Window::manageEvents(){
    if(eventLoop) eventLoop();
}

void Window::run(){
    while(running){
        render();
        manageEvents();
        if(renderCallback) renderCallback();
        if(logicalLoop) logicalLoop();
    }
}

SDL_Renderer* Window::getRenderer(){
    return renderer;
}

SDL_Window* Window::getWindow(){
    return window;
}

void Window::setLogicalResolution(float w, float h, SDL_RendererLogicalPresentation presentation){
    SDL_SetRenderLogicalPresentation(renderer, (int)w, (int)h, presentation);
}

void Window::setRenderCallback(callback cb){
    renderCallback = cb;
}

void Window::setLogicalLoop(callback ll){
    logicalLoop = ll;
}

void Window::setEventLoop(callback el){
    eventLoop = el;
}

void Window::setRunning(bool running){
    this->running = running;
}