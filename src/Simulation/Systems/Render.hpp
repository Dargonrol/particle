#pragma once

#include "../Components/Renderable.h"
#include <entt/entt.hpp>

namespace Systems
{
void RenderSystem(entt::registry &registry)
{
}

void ColorSystem(entt::registry &registry)
{
    auto view = registry.view<Components::Color>();

    for (auto [entity, color] : view->each())
    {
        color.value = {255, 0, 0, 255};
    }
}
} // namespace Systems