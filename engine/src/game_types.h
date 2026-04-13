#pragma once

#include "core/application.h"

struct game {

    //app config
    application_config app_config;

    //function pointer to games init function
    b8 (*initialize)(struct game* game_inst);

    //function pointer to game's update function
    b8 (*update)(struct game* game_inst, f32 delta_time);

    //function pointer to game's render function
    b8(*render)(struct game* game_inst, f32 delta_time);

    //function pointer to handle resizes 
    void (*on_resize)(struct game* game_inst, u32 width, u32 height);

    //state managed by game class
    void* state;
    
    

};
