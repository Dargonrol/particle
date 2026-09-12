#pragma once

class App;

class Layer
{
  public:
    explicit Layer(App &app) : application(app) {}
    virtual ~Layer() = default;

    virtual void Init();
    virtual void Update(float deltaTime);
    virtual void Render() = 0;

    virtual void OnEnter();
    virtual void OnLeave();
    virtual void OnResize();

  public:
    bool active = true;

  private:
    App &application;
};