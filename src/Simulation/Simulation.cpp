#include "Simulation.h"
#include "Systems/Physics.hpp"
#include "Systems/Render.hpp"

void Simulation::Update(float deltaTime)
{
    // Systems updates: execute async!
    // Input
    // Movement
    Systems::PhysicsSystem(registry, deltaTime);
    Systems::ColorSystem(registry);
    // Sounds
    // Cleanup
}

void Simulation::Render()
{
    Systems::RenderSystem(registry);
}

void RemoveParticles(unsigned int count) {}
void RemoveParticles(unsigned int count, glm::vec2 pos, float radius) {}
void AddParticles(unsigned int count) {}
void AddParticles(unsigned int count, glm::vec2 pos, float radius) {}
void SetParticles(unsigned int count) {}