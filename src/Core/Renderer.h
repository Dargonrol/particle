#pragma once

#include "../Simulation/Particle.h"
#include <raylib.h>
#include <vector>

class App;

class Renderer
{
  public:
    explicit Renderer(App &app);
    ~Renderer();

    void Init();
    void Render(float a, float b);
    void Update(const float deltaTime);

    void ResizeEvent();

  private:
    void RenderUI(float a, float b);
    void RenderViewport();
    void SpawnParticles();
    Color GetHeatmapColor(float speed, float maxSpeed);
    Color GetTimeBasedColor(float speed, float maxSpeed);
    void RenderParticles(const std::vector<Particle> &particles);

  private:
    App &application;
    float uiWidth = 300.0f;
    int viewportWidth;
    int viewportHeigth;

    RenderTexture2D viewportTarget;

    // ui
    int particlesCount = 100000;
    int prevParticleCount = 10000;
    float particleSize = 1.0f;
    float friction = 1.0f;
    float gravitationalPull = 5000.0f;
    float gravitationalRadius = 10000.0f;

    Vector2 mousePos;

    std::vector<Particle> particles;
};