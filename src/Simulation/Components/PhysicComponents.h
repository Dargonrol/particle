#pragma once

#include <glm/vec2.hpp>

namespace Components
{
struct Velocity
{
    glm::vec2 value;
};

struct RidigBody
{
    float mass{1.0f};
    glm::vec2 force;
};

struct AffectedByPhysics
{
};
struct AffectedByGravity
{
};
struct AffectedByPlayer
{
};
struct AffectedByWind
{
};
struct AffectedByNodes
{
};

struct WindResistance
{
    float coefficient{1.0f};
};
} // namespace Components