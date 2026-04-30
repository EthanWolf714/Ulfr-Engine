#include <entry.h>
#include <game.h>

//TODO: remove eventuatlly
#include <platform/platform.h>

//define to create a game
b8 create_game(game* out_game){
    //game sets app configs
    out_game->app_config.start_pos_x = 100;
    out_game->app_config.start_pos_y = 100;
    out_game->app_config.start_width = 1280;
    out_game->app_config.start_height = 720;
    out_game->app_config.name = "Fimbul Engine";
    out_game->update = game_update;
    out_game->render = game_render;
    out_game->initialize = game_initialize;
    out_game->on_resize = game_on_resize;

    //allocate memory for game state
    out_game->state = (game_state*)memory.falloc(sizeof(game_state), MEMORY_TAG_GAME);
    return TRUE;
}

