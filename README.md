 # Ulfr Engine

 ### Decription
 A Doom style engine in C++ built with ralyib

 ### Goals
 Goal is make a viking themed retro first person game useing the engine once it is complete enough as well as use them both as resume projects.

 ### Stack
- [Raylib](https://github.com/raysan5/raylib) — Core framework
- [Dear ImGui](https://github.com/ocornut/imgui) — Editor UI
- [rlImGui](https://github.com/raylib-extras/rlImGui) — Raylib/ImGui binding
- [cglm](https://github.com/recp/cglm) — Math library
- [cJSON](https://github.com/DaveGamble/cJSON) — Level data format
- [Native File Dialog Extended](https://github.com/btzy/nativefiledialog-extended) — File dialogs
- [miniaudio](https://github.com/mackron/miniaudio) — Audio
- [Earcut](https://github.com/nicowillis/earcut.c) — Polygon triangulation
- [Chipmunk2D](https://github.com/slembcke/Chipmunk2D) — Physics

### Architecture

ulfr-engine/
├── src/
│   ├── main.cpp                    ← entry point only
│   ├── engine/
│   │   ├── Engine.h/.cpp           ← core engine class
│   │   ├── Renderer.h/.cpp         ← all rlgl and BeginMode3D
│   │   ├── Camera.h/.cpp           ← wraps Camera3D
│   │   ├── TextureManager.h/.cpp   ← load/cache/unload textures
│   ├── game/
│   │   ├── Map.h/.cpp
│   └── editor/
│       ├── Editor.h/.cpp
├── include/
├── assets/
│   └── textures/
├── libs/
│   ├── imgui/
│   └── rlimgui/
├── build/
└── CMakeLists.txt

### Build instructions
Coming soon!
