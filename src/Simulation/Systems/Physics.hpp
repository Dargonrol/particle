#pragma once

#include "../Components/PhysicComponents.h"
#include "../Components/Transform.h"

#include "entt/entt.hpp"

namespace Systems
{
using namespace Components;

void PhysicsSystem(entt::registry &registry, float deltaTime)
{
    auto view = registry.view<Position, Velocity, RidigBody, AffectedByPhysics>();

    for (auto [entity, position, velocity, body] : view.each())
    {
        // acceleration = force / mass
        glm::vec2 acceleration = body.force / body.mass;

        velocity.value += acceleration * deltaTime;

        position.value += velocity.value * deltaTime;

        body.force.x = 0;
        body.force.y = 0;
    }
}

} // namespace Systems
