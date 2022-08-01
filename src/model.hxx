#pragma once

#include <ge211.hxx>
#include "game_config.hxx"
#include "piece.hxx"

#include <map>
#include <iostream>
#include <vector>
#include <string>

enum class MoveType
{
    attack,
    move,
    none
};

struct MoveOption {
    ge211::Posn<int> o_posn;
    MoveType o_move_type;
};

enum class GameState
{
    start,
    intro_placing,
    placing,
    choosing,
    one_select_guess_or_attack,
    attacker_views_attacking,
    guessing_views_attacking,
    victim_views_attacking,
    pausing,
    game_over,
    guessing
};
enum class Turn
{
    blue,
    red
};

class Model
{
    // PRIVATE MEMBER VARIABLES
    GameState game_state_ = GameState::start;
    Turn turn = Turn::red;

public:
    using Position = ge211::Posn<int>;
    /// PUBLIC MEMBER VARIABLES
    // Game_config config;
    std::map<int,int> unplaced_red;
    int left_to_place=30;
    std::map<int,int> unplaced_blue;
    int off_grid[13]={-1,0,1,2,3,4,5,6,
                      7,8,9,10,11};
    int off_grid_sprites[13];
    Piece board [8][10] ={{Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none)},
                      {Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none)},
                      {Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none)},
                      {Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none)},
                      {Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none)},
                      {Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none)},
                      {Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none)},
                      {Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none),
                              Piece(0,Position(0,0),Team::none)}};
    Piece curr_piece=Piece(0,Position(-1,-1),Team::none);
    std::vector<MoveOption> curr_piece_possibilities={};
    // used for guesses
    int spotter_guess=-5;
    Piece victim_piece=Piece(0,Position(-1,-1),Team::none);
    // used to show attacker stuff
    bool attacking_must_be_shown_to_victim=false;

    // CONSTRUCTOR
    Model();
    // to get info for model
    GameState game_state() const;
    Turn get_turn() const;
    int get_blue_unplaced_amount(int) const;
    int get_red_unplaced_amount(int) const;

    // FUNCTIONS
    void change_turn();
    void set_curr_piece(Piece);
    // placing stage
    void place_piece(Position posn);
    void place_or_set_to_place(Position posn);
    // guessing stage
    void guess_or_attack(Position posn);
    void guess_piece(Position posn);
    void see_if_guess_right();
    // choosing / attacking phase
    void act_or_set_new_act(Position posn);
    void act_on_possibility(Position);
        void show_attack_matchup(Position);
        void attack_piece();
        void move_piece(Position);
    void display_possibilities();
    void change_game_state(GameState);

    void on_frame(double dt);

};
