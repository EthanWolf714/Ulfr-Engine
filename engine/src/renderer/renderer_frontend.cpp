#include "renderer_frontend.h"
renderer_frontend renderer;

b8 renderer_frontend::initialize(const char* app_name, platform_state* plat_state){
    memory.falloc(sizeof(backend), MEMORY_TAG_RENDERER);

    backend.set_frame_num(0);
   if(!backend.initialize(app_name, plat_state)){
        FERROR("Renderer backend failed to initialize. Shutting down.");
        return FALSE;
   }
   return TRUE;
}

void renderer_frontend::shutdown(){
    backend.shutdown();
}
void renderer_frontend::resized(u16 width, u16 height){
    return backend.resize(width, height);
}

b8 renderer_frontend::begin_frame(f32 delta_time)
{
    return backend.begin_frame(delta_time);

}

b8 renderer_frontend::end_frame(f32 delta_time)
{
    b8 result = backend.end_frame(delta_time);
    backend.set_frame_num(backend.get_frame_num() + 1);
    return result;
}


b8 renderer_frontend::draw_frame(render_packet* packet){
    if(begin_frame(packet->delta_time)){

        //end the frame. if it failes it is likely unrecoverable
        b8 result = end_frame(packet->delta_time);

        if(!result){
            FERROR("endframe failed. Application shutting down...");
            return FALSE;
        }
    }
    return TRUE;
}