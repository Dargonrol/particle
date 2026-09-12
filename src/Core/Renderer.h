#pragma once

class App;

class Renderer
{
  public:
    explicit Renderer(App &app);
    ~Renderer() = default;

    void Render();
    void Update(const float deltaTime);

    void OnResize();
    void OnEnter();
    void OnLeave();

  private:
    App &application;
};