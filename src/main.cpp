#include <raylib.h>

#include "Renderer.h"

int main()
{

    float speed = 0;

    Renderer renderer(1920, 1000);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_H))
        {
            if (IsCursorHidden())
                ShowCursor();
            else
                HideCursor();
        }

        renderer.Update(GetFrameTime());
        renderer.Render();
    }

    return 0;
}

void Render();