#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "rlImGui.h"
#include "imgui.h"
#include "Renderer.h"
#include "Camera.h"
#include "TextureManager.h"
#include "game/Map.h"
#include "game/Player.h"
#include "Logger.h"
#include "editor/Editor.h"
#include "InputHandler.h"


enum class EngineMode
{
    Game,
    Editor
};
class Engine {
    public:
        
        void Run();
        
    
    private:
        void Update(float dt);
        void Render();
        void SetMode(EngineMode mode);
        void ShutDown();
        void Init();

        //subsystems
        Editor m_editor;
        EngineMode m_mode = EngineMode::Editor;
        Renderer m_renderer;
        GameCamera m_camera;
        InputHandler    m_input;
        TextureManager m_textureManager;
        bool m_running = false;
        Map m_map;
        Player m_player;
        
        
        
       

      

};

