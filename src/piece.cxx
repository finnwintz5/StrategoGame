#include "piece.hxx"
#include "game_config.hxx"

Game_config local_config_2;



Piece::Piece(int type, Position posn,Team team)
    : p_type(type),
    p_posn(posn),
    p_team(team),
    p_sprite(ge211::Image_sprite("board.png"))
{
    if (team==Team::blue) {

        p_sprite=ge211::Image_sprite("blue-"+ std::to_string(type) + ""
                                                                         ".png");

    }
    else if (team==Team::red) {
        p_sprite=ge211::Image_sprite("red-"+ std::to_string(type) + ""
                                                                     ".png");
    }
}
