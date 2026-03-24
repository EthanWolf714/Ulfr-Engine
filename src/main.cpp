#include "raylib.h"
#include "engine/Engine.h"

int main()
{
    Engine engine;
    engine.Init();
    engine.Run();
    engine.ShutDown();
    return 0;
}