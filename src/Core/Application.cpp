#include "Application.h"
#include "Renderer.h"
#include <iostream>
#include <memory>
#include <raylib.h>

App::~App() { CloseWindow(); }

void App::Init()
{
    InitWindow(windowWidth, windowHeight, "Window");
    SetTargetFPS(144);

    renderer = std::make_unique<Renderer>(*this);
}

void App::Run()
{
    renderer->Init();
    while (!WindowShouldClose())
    {
        if (IsWindowResized())
        {
            renderer->ResizeEvent();
        }
        renderer->Update(GetFrameTime());
        renderer->Render(2, 2);
    }
}

void App::SetSize(int width, int height)
{
    SetWindowSize(width, height);
    windowWidth = width;
    windowHeight = height;
    renderer->ResizeEvent();
}
void App::SetMaxSize(int width, int height) { SetWindowMaxSize(width, height); }
void App::SetMinSize(int width, int height) { SetWindowMinSize(width, height); }
void App::SetTitle(std::string_view title) { SetWindowTitle(std::string(title).c_str()); }
void App::SetWindowConfig(int flags) { SetConfigFlags(flags); }
void App::SetWindowFlags(int flags) { SetWindowState(flags); }
void App::SetFPSTarget(int targetFPS) { SetTargetFPS(targetFPS); }
void App::SetVSync(bool active) {}
