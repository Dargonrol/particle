#include "Core/Application.h"
#include <raylib.h>

int main()
{
    App app{};

    app.SetWindowConfig(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    app.Init();
    app.SetWindowFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    app.SetFPSTarget(144);
    app.SetSize(1920, 1000);
    app.SetTitle("Particle Simulation");
    app.SetMinSize(600, 300);

    app.Run();

    return 0;
}