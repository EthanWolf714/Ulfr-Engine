#pragma once
#include "raylib.h"
#include "rlgl.h"

class Renderer
{
    public:
        void Init();
        void Update();
        void ShutDown();
        void Draw(Camera& camera);
    private:
        Texture2D m_testTexture;
};