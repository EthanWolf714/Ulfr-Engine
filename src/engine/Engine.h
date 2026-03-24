#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "Renderer.h"
class Engine {
    public:
        void Init();
        void Run();
        void ShutDown();

    private:
        void Update();
        void Render();
        Renderer m_renderer;
        Camera3D m_camera;
        bool m_running = false;

};