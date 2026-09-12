#pragma once

#include <entt/entt.hpp>
#include <glm/fwd.hpp>

class Simulation
{
  public:
    Simulation() = default;
    ~Simulation() = default;

    void Init();
    void Update(float deltaTime);
    void Render();

    void RemoveParticles(unsigned int count);
    void RemoveParticles(unsigned int count, glm::vec2 pos, float radius);
    void AddParticles(unsigned int count);
    void AddParticles(unsigned int count, glm::vec2 pos, float radius);
    void SetParticles(unsigned int count);

  private:
    entt::registry registry;
};