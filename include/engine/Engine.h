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
#include "engine/Logger.h"
#include "editor/Editor.h"

class Engine {
    public:
        void Init();
        void Run();
        void ShutDown();
    
    private:
        void Update();
        void Render();
        Editor m_editor;
        Renderer m_renderer;
        GameCamera m_camera;
        TextureManager m_textureManager;
        bool m_running = false;
        Map m_map;
        Player m_player;
        
        
       

      

};