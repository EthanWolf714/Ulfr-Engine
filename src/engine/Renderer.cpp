#include "Renderer.h"

void Renderer::Init()
{
    m_testTexture = LoadTexture("assets/pics/greystone.png");
}

void Renderer::Update()
{

}

void Renderer::ShutDown()
{
    UnloadTexture(m_testTexture);
}

void Renderer::Draw(Camera& camera)
{
    BeginMode3D(camera);
        rlDisableBackfaceCulling();
            DrawGrid(10,1.0f);
            rlSetTexture(m_testTexture.id);
            rlBegin(RL_QUADS);
                // front face of a wall quad
                // x is left/right, y is up/down, z is depth
                rlTexCoord2f(0.0f, 0.0f);
                rlVertex3f(-1.0f,  1.0f, 0.0f); // top left

                rlTexCoord2f(0.0f, 1.0f);
                rlVertex3f(-1.0f, -1.0f, 0.0f); // bottom left

                rlTexCoord2f(1.0f, 1.0f);
                rlVertex3f( 1.0f, -1.0f, 0.0f); // bottom right

                rlTexCoord2f(1.0f, 0.0f);
                rlVertex3f( 1.0f,  1.0f, 0.0f); // top right
            rlEnd();
            rlSetTexture(0);
        EndMode3D();
}