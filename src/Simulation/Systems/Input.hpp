#pragma once

#include "../Components/PhysicComponents.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <raylib.h>

namespace Systems
{
using namespace Components;

void PlayerInputSystem(entt::registry &registry)
{
    struct MouseState
    {
        union
        {
            std::uint8_t state;

            struct
            {
                std::uint8_t leftButton : 1 = 0;
                std::uint8_t rightButton : 1 = 0;
                std::uint8_t reserved : 6 = 0;
            };
        };

        [[nodiscard]] bool AnyPressed() { return state; }

    } mouseState;

    mouseState.leftButton = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    mouseState.rightButton = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);

    if (mouseState.AnyPressed())
    {
    }
}
} // namespace Systems