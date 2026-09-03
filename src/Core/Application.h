#pragma once
#include "Renderer.h"
#include <memory>
#include <string_view>

#include <raylib.h>

class App
{
  public:
    App() = default;
    ~App();

    void Init();
    void Run();

    void SetSize(int width, int height);
    void SetTitle(std::string_view title);
    void SetMaxSize(int width, int height);
    void SetMinSize(int width, int height);
    void SetWindowConfig(int flags);
    void SetWindowFlags(int flags);
    void SetFPSTarget(int targetFPS);
    void SetVSync(bool active);

    [[nodiscard]] int GetWindowWidth() const { return windowWidth; }
    [[nodiscard]] int GetWindowHeight() const { return windowHeight; }
    [[nodiscard]] Renderer &GetRenderer() { return *renderer; }
    [[nodiscard]] const Renderer &GetRenderer() const { return *renderer; }

  private:
    int windowWidth = 720;
    int windowHeight = 400;

    std::unique_ptr<Renderer> renderer;
};