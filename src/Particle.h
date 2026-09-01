#pragma once

#include <glm/glm.hpp>
#include <raylib.h>

struct Particle
{
    glm::vec2 pos;
    glm::vec2 vel;

    Color col;
};