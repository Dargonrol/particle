#pragma once

#include <glm/glm.hpp>
#include <raylib.h>

struct Particle
{
    glm::vec2 pos = {0.0f, 0.0f};
    glm::vec2 vel = {0.0f, 0.0f};

    Color col = {255, 0, 0, 255};
};