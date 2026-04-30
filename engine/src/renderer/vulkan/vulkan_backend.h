#pragma once 
#include "defines.h"
#include "core/logger.h"
#include "vulkan_types.inl"

struct platform_state;

class vulkan_backend {
    public:
        b8 initialize(const char* application_name, struct platform_state* plat_state);
        void shutdown();
        void resize(u16 width, u16 height);
        b8 begin_frame(f32 delta_time);
        b8 end_frame(f32 delta_time);
        void set_frame_num(u64 num);
        u64 get_frame_num();

    private:
        vulkan_context context;
        u64 frame_number;
};

