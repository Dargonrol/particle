#include "Renderer.h"

#ifndef RAYGUI_STATIC
#define RAYGUI_STATIC
#endif

#include "raygui.h"

#include "Particle.h"
#include <cmath>
#include <glm/common.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <raylib.h>
#include <rlgl.h>

Renderer::Renderer(int width, int heigth) : windowWidth(width), windowHeight(heigth)
{
    InitWindow(windowWidth, windowHeight, "Raylib - UI & Viewport Split");
    SetTargetFPS(144);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    viewportTarget = LoadRenderTexture(viewportWidth, viewportHeigth);

    SpawnParticles();
}

Renderer::~Renderer()
{
    UnloadRenderTexture(viewportTarget);
    CloseWindow();
}

void Renderer::Render()
{
    RenderViewport();

    BeginDrawing();
    {
        ClearBackground(LIGHTGRAY);
        // viewport
        Rectangle sourceRec = {0.0f, 0.0f, static_cast<float>(viewportWidth), -static_cast<float>(viewportHeigth)};
        Rectangle destRec = {uiWidth, 0.0f, static_cast<float>(viewportWidth), static_cast<float>(viewportHeigth)};

        Vector2 origin = {0.0f, 0.0f};

        DrawTexturePro(viewportTarget.texture, sourceRec, destRec, origin, 0.0f, WHITE);

        RenderUI();
    }
    EndDrawing();
}

void Renderer::RenderUI()
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, 15);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RAYWHITE));

    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, ColorToInt(GetColor(0x333333FF)));

    // background
    DrawRectangle(0, 0, (int)uiWidth, windowHeight, GetColor(0x202020FF));

    // seperation line
    DrawLine((int)uiWidth, 0, (int)uiWidth, windowHeight, GRAY);

    // ui elements
    GuiGroupBox({10, 10, uiWidth - 20, 200}, "CONTROLS");

    float currentY = 35.0f;
    const float paddingX = 20.0f;
    const float controlWidth = uiWidth - 40.0f;
    const float sliderWidth = controlWidth - 50.0f;
    const float labelHeigth = 20.0f;
    const float sliderHeigth = 24.0f;
    const float spacing = 12.0f;

    float tmp = static_cast<float>(particlesCount);
    GuiLabel(
        {paddingX, currentY, controlWidth, labelHeigth},
        "Particle Count");
    currentY += labelHeigth;
    GuiSlider(
        {paddingX, currentY, sliderWidth, sliderHeigth},
        nullptr,
        TextFormat("%d", particlesCount),
        &tmp,
        0.0f,
        1000000.0f);
    prevParticleCount = particlesCount;
    particlesCount = static_cast<int>(tmp);
    currentY += sliderHeigth;
    GuiLabel(
        {paddingX, currentY, controlWidth, labelHeigth},
        "Particle Size");
    currentY += labelHeigth;
    GuiSlider(
        {paddingX, currentY, sliderWidth, sliderHeigth},
        nullptr,
        TextFormat("%.1f", particleSize),
        &particleSize,
        0.0f,
        100.0f);
    currentY += sliderHeigth;
    GuiLabel(
        {paddingX, currentY, controlWidth, labelHeigth},
        "Friction");
    currentY += labelHeigth;
    GuiSlider(
        {paddingX, currentY, sliderWidth, sliderHeigth},
        nullptr,
        TextFormat("%.1f", friction),
        &friction,
        -10.0f,
        10.0f);
    currentY += sliderHeigth;
    GuiLabel(
        {paddingX, currentY, controlWidth, labelHeigth},
        "Gravitational Pull");
    currentY += labelHeigth;
    GuiSlider(
        {paddingX, currentY, sliderWidth, sliderHeigth},
        nullptr,
        TextFormat("%.1f", gravitationalPull),
        &gravitationalPull,
        0.0f,
        10000.0f);
    currentY += sliderHeigth;
    GuiLabel(
        {paddingX, currentY, controlWidth, labelHeigth},
        "Gravitational Pull Radius");
    currentY += labelHeigth;
    GuiSlider(
        {paddingX, currentY, sliderWidth, sliderHeigth},
        nullptr,
        TextFormat("%.1f", gravitationalRadius),
        &gravitationalRadius,
        0.0f,
        10000.0f);
    currentY += sliderHeigth;

    DrawText(TextFormat("FPS: %d (%.2f ms)", GetFPS(), GetFrameTime()), paddingX, windowHeight - 25, 20, GREEN);
}

void Renderer::RenderParticles(const std::vector<Particle> &particles)
{
    for (const auto &item : particles)
    {
        Vector2 pos = {item.pos.x, item.pos.y};
        Vector2 size = {particleSize, particleSize};

        DrawRectangleV(pos, size, item.col);
    }
}

void Renderer::RenderViewport()
{
    BeginTextureMode(viewportTarget);
    {
        ClearBackground(BLACK);
        DrawGrid(10, 50.0f);
        RenderParticles(particles);
        DrawCircleLines(mousePos.x, mousePos.y, gravitationalRadius, WHITE);
    }
    EndTextureMode();
}

void Renderer::Update(const float deltaTime)
{
    if (particlesCount != prevParticleCount || (IsKeyPressed(KEY_R)))
        SpawnParticles();

    const bool isMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    const bool isMouseDown2 = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
    mousePos = GetMousePosition();
    const bool isMouseInViewport = mousePos.x >= uiWidth;
    mousePos.x -= uiWidth;

    const int count = static_cast<int>(particles.size());
    float forceMultiplier = 0.0f;

    if (isMouseInViewport)
    {
        if (isMouseDown)
            forceMultiplier = 1.0f;
        else if (isMouseDown2)
            forceMultiplier = -1.0f;
    }

    const float radiusSquared = gravitationalRadius * gravitationalRadius;
    float waveFreq = 0.08f;
    float timePulse = GetTime() * 4.0f;

    for (int i = 0; i < count; ++i)
    {
        Particle &particle = particles[i];

        if (particle.pos.x <= 0 || particle.pos.x >= viewportWidth)
            particle.vel.x *= -1;
        if (particle.pos.y <= 0 || particle.pos.y >= viewportHeigth)
            particle.vel.y *= -1;

        if (forceMultiplier != 0)
        {
            glm::vec2 direction = glm::vec2{mousePos.x, mousePos.y} - particle.pos;
            float distSq = direction.x * direction.x + direction.y * direction.y;

            if (distSq <= radiusSquared && distSq > 0.001f)
            {
                float distance = glm::length(direction);
                direction /= distance;
                glm::vec2 rotationDir = glm::vec2{-direction.y, direction.x};

                float wave = std::sin(distance * waveFreq - timePulse);

                float baseForce = (gravitationalPull * forceMultiplier) / (distance * 0.05f + 1.0f);

                float pullForce = baseForce * wave;
                float angle = std::atan2(direction.y, direction.x);
                float spiralArms = std::sin(angle * 4.0f + distance * 0.05f);

                float swirlForce = baseForce * (1.5f + spiralArms * 0.8f);

                glm::vec2 totalForce = (direction * pullForce) + (rotationDir * swirlForce);

                particle.vel += totalForce * deltaTime;
            }
        }

        particle.vel -= (particle.vel * friction) * deltaTime;

        particle.vel = clamp(particle.vel, -1000.0f, 1000.0f);

        particle.pos += particle.vel * deltaTime;

        particle.col = GetTimeBasedColor(glm::length(particle.vel), 5000.0f);
    }
}

void Renderer::SpawnParticles()
{
    particles.clear();
    particles.reserve(particlesCount);
    for (int i = 0; i < particlesCount; ++i)
    {
        particles.push_back(Particle{
            .pos = {GetRandomValue(0, viewportWidth * 100) / 100.0f, GetRandomValue(0, viewportHeigth * 100) / 100.0f},
            .vel = {0, 0},
            .col = {255, 0, 0, 255}});
    }
}

Color Renderer::GetHeatmapColor(float speed, float maxSpeed)
{
    float normalized = glm::clamp(speed / maxSpeed, 0.0f, 1.0f);

    if (normalized < 0.5f)
    {
        float factor = normalized * 2.0f;
        return ColorLerp(BLUE, GREEN, factor);
    }
    else
    {
        float factor = (normalized - 0.5f) * 2.0f;
        return ColorLerp(GREEN, RED, factor);
    }
}

Color Renderer::GetTimeBasedColor(float speed, float maxSpeed)
{
    float hue = std::fmod(GetTime() * 30.0f, 360.0f);

    hue = std::fmod(hue + (speed * 0.5f), 360.0f);

    return ColorFromHSV(hue, 0.9f, 1.0f);
}
