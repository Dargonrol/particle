#pragma once

#include "Particle.h"
#include <raylib.h>
#include <vector>

class Renderer
{
  public:
    explicit Renderer(int width, int heigth);
    ~Renderer();

    void Render();
    void Update(const float deltaTime);

  private:
    void RenderUI();
    void RenderViewport();
    void SpawnParticles();
    Color GetHeatmapColor(float speed, float maxSpeed);
    Color GetTimeBasedColor(float speed, float maxSpeed);

  private:
    int windowWidth = 1200;
    int windowHeight = 720;

    const float uiWidth = 300.0f;
    const int viewportWidth = windowWidth - static_cast<int>(uiWidth);
    const int viewportHeigth = windowHeight;

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