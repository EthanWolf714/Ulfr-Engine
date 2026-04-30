#include "game.h"

#include <core/logger.h>

//game methods pass game instance to get game data
b8 game_initialize(game* game_inst){
    FDEBUG("game initialized was called!");
    return TRUE;
}
//game update loop
b8 game_update(game* game_inst, f32 delta_time){
    return TRUE;
}

//game rendering
b8 game_render(game* game_inst, f32 delta_time){
    return TRUE;
}
//resizeing game window
void game_on_resize(game* game_inst, u32 width, u32 height){

}