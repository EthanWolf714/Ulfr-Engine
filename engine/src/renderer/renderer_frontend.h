#pragma once
#include "defines.h"
#include "core/logger.h"
#include "core/fmemory.h"
#include "renderer_types.h"
#include "vulkan/vulkan_backend.h"
class renderer_frontend {
    public:
        b8 initialize(const char* app_name, platform_state* plat_state);
        void shutdown();
        void resized(u16 width, u16 height);
        b8 begin_frame(f32 delta_time);
        b8 end_frame(f32 delta_time);
        b8 draw_frame(render_packet* packet);

    private:
    vulkan_backend backend;
    
};

extern FAPI renderer_frontend renderer;