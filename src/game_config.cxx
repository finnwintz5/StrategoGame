#include "game_config.hxx"

// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        : counter_left(0),
          counter_right(800),
          top_counter(300),
          bottom_counter(630),
          scene_dims({1024, 768})
{
    for(int i=0;i<4;i++) {
        counter_y_posns.push_back(top_counter + i*
                (bottom_counter-top_counter)/3);
    }
}
