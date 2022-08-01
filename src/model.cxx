#include "model.hxx"
#include <chrono>
#include <thread>

Model::Model()
{
    int piece_nums[13]={1,1,2,5,5,
                        2,2,2,1,1,
                        1,1,6};
    Position start_posn=Position(0,0);
    // initialize unplaced pieces
    for (int i=-1;i<12;i++) {
        unplaced_red[i]=piece_nums[i+1];
        unplaced_blue[i]=piece_nums[i+1];
    }
    // initialize empty board
    //
    // for (int i=0;i<8;i++) {
    //     for (int j=0;j<10;j++) {
    //         board[i][j]=Piece(0,Position(0,0),Team::none);
    //     }
    // }
    // initialize pit spaces
    for (int i=3;i<5;i++) {
        board[i][2].p_team=Team::pit;
        board[i][3].p_team=Team::pit;
        board[i][6].p_team=Team::pit;
        board[i][7].p_team=Team::pit;
    }
}

/// ================ RETURNING STATE OF MODEL ================

void
Model::change_turn()
{
    if (turn==Turn::red) {
        turn=Turn::blue;
    }
    else if (turn==Turn::blue) {
        turn=Turn::red;
    }
}

int
Model::get_blue_unplaced_amount(int num) const
{
    return unplaced_blue.at(num);
}

int
Model::get_red_unplaced_amount(int num) const
{
    return unplaced_red.at(num);
}

Turn
Model::get_turn() const
{
    return turn;
}

GameState
Model::game_state() const
{
    return game_state_;
}

/// ================ SIMPLE FUNCTIONS UBIQUITOUS ================

void
Model::change_game_state(GameState state) {
    game_state_=state;
}

void
Model::set_curr_piece(Piece piece)
{
    curr_piece=piece;
}

/// ================ FUNCTIONS FOR PLACING STAGE ================

void
Model::place_piece(Position posn)
{
    if (posn.x>=0 && posn.y>=0 && posn.x<10 && posn.y<8) {
        // position in bounds
        if (board[posn.y][posn.x].p_team==Team::none) {
            // allowed to place piece (probably)
            if (turn==Turn::red) {
                if (posn.y<3) {
                    // place
                    board[posn.y][posn.x]=Piece(curr_piece.p_type,posn,
                                                curr_piece.p_team);
                    unplaced_red[curr_piece.p_type]-=1;
                    if (unplaced_red[curr_piece.p_type]<=0) {
                        set_curr_piece(Piece(0,Position(0,0),Team::none));
                    }
                    left_to_place-=1;
                }
            }
            else if (turn==Turn::blue) {
                if (posn.y>4) {
                    board[posn.y][posn.x]=Piece(curr_piece.p_type,posn,
                                                curr_piece.p_team);
                    unplaced_blue[curr_piece.p_type]-=1;
                    if (unplaced_blue[curr_piece.p_type]<=0) {
                        set_curr_piece(Piece(0,Position(0,0),Team::none));
                    }
                    left_to_place-=1;
                }
            }
        }
    }
    if (left_to_place<=0) {
        left_to_place=30;
        if (turn==Turn::blue) {
            game_state_=GameState::choosing;
        }
        else if (turn==Turn::red) {
            game_state_=GameState::intro_placing;
        }
        change_turn();
    }
}

void
Model::place_or_set_to_place(Position mouse_in_grid)
{
    //place action
    if (curr_piece.p_team==Team::none || curr_piece.p_team==Team::pit || mouse_in_grid.y>7) {
        if(mouse_in_grid.y==8) {
            int piece_type=off_grid[mouse_in_grid
                    .x];
            if ((get_turn()==Turn::red &&
                 unplaced_red[piece_type]>0)) {
                set_curr_piece(Piece(piece_type,
                                            Position(0,0),Team::red));
            }
            else if (get_turn()==Turn::blue &&
                     unplaced_blue[piece_type]>0) {
                set_curr_piece(Piece(piece_type,
                                            Position(0,0),Team::blue));
            }
        }
        else if (mouse_in_grid.y==9 && mouse_in_grid.x<3) {
            int piece_type=off_grid[mouse_in_grid
                                                   .x+10];
            if ((get_turn()==Turn::red &&
                 unplaced_red[piece_type]>0)) {
                set_curr_piece(Piece(piece_type,
                                            Position(0,0),Team::red));
            }
            else if (get_turn()==Turn::blue &&
                     unplaced_blue[piece_type]>0) {
                set_curr_piece(Piece(piece_type,
                                            Position(0,0),Team::blue));
            }

        }
        // set / reset curr_piece
        // need to relate mouse_in_grid to the off board placing pieces
        // here we have to check to make sure we're allowed to as well
    }
    else {
        place_piece(mouse_in_grid);
    }
}

/// ================ FUNCTIONS FOR GUESSING STAGE ================

void
Model::guess_or_attack(Position posn)
{
    if(posn==Position(1,8)) {
        // guess
        change_game_state(GameState::guessing);
    } else if(posn==Position(2,8)) {
        // attack
        show_attack_matchup(victim_piece.p_posn);
    }
}

void
Model::guess_piece(Position mouse_in_grid)
{
    if(mouse_in_grid.y==8) {
        spotter_guess=off_grid[mouse_in_grid.x];
        see_if_guess_right();
    }
    else if (mouse_in_grid.y==9 && mouse_in_grid.x<3) {
        spotter_guess=off_grid[mouse_in_grid
                                        .x+10];
        see_if_guess_right();
    }
    attacking_must_be_shown_to_victim=true;
    change_game_state(GameState::guessing_views_attacking);
}

void
Model::see_if_guess_right()
{
    if (victim_piece.p_type==spotter_guess) {
        board[victim_piece.p_posn.y][victim_piece.p_posn.x].p_team=Team::none;
        std::cout<<"guess correct\n";
    }
    else {
        board[curr_piece.p_posn.y][curr_piece.p_posn.x].p_team=Team::none;
        std::cout<<"guess incorrect\n";
    }
    change_turn();
}


void
Model::move_piece(Position next)
{

    board[next.y][next.x]=Piece(curr_piece.p_type,next,curr_piece.p_team);
    board[curr_piece.p_posn.y][curr_piece.p_posn.x]=Piece(0,curr_piece.p_posn,Team::none);
    game_state_=GameState::pausing;
    change_turn();
}

void
Model::show_attack_matchup(Position victim)
{
    victim_piece=board[victim.y][victim.x];
    change_game_state(GameState::attacker_views_attacking);
}

void
Model::attack_piece()
{
    // anyone attacks flag
    Position victim=victim_piece.p_posn;

    if (victim_piece.p_type==-1) {
        board[victim.y][victim.x].p_team=Team::none;
        move_piece(victim);
        change_game_state(GameState::game_over);
    }
    // spy attacks marshall
    else if (curr_piece.p_type==0 && victim_piece.p_type==10) {
        // spy wins
        board[victim.y][victim.x].p_team=Team::none;
        move_piece(victim);
    }
    // miner excavates bomb
    else if (curr_piece.p_type==3 && victim_piece.p_type==11) {
        //miner wins
        board[victim.y][victim.x].p_team=Team::none;
        move_piece(victim);
    }
    // general case
    else if (victim_piece.p_type>curr_piece.p_type) {
        // victim wins
        board[curr_piece.p_posn.y][curr_piece.p_posn.x].p_team=Team::none;
        game_state_=GameState::pausing;
        change_turn();
    }
    else if (victim_piece.p_type<curr_piece.p_type) {
        // attacker wins & moves to victim space
        board[victim.y][victim.x].p_team=Team::none;
        move_piece(victim);
    }
    else {
        // both die
        board[curr_piece.p_posn.y][curr_piece.p_posn.x].p_team=Team::none;
        board[victim.y][victim.x].p_team=Team::none;
        game_state_=GameState::pausing;
        change_turn();
    }
    attacking_must_be_shown_to_victim=true;
}

void
Model::act_or_set_new_act(Position posn)
{
    if (posn.x>=0 && posn.x<10 && posn.y>=0 && posn.y<8) {
        Team curr_team=board[posn.y][posn.x].p_team;
        if ((curr_team==Team::red && get_turn()
        ==Turn::red) || (curr_team==Team::blue && get_turn()==Turn::blue)) {
            set_curr_piece(board[posn.y][posn.x]);
            display_possibilities();
        }
        else {
            act_on_possibility(posn);
        }
    }
}

void
Model::act_on_possibility(Position posn)
{
    for (int i=0;i<curr_piece_possibilities.size();i++) {
        if (curr_piece_possibilities[i].o_posn==posn) {
            if (curr_piece_possibilities[i]
                        .o_move_type==MoveType::attack && curr_piece
                        .p_type==1) {
                // choose whether to attack or guess

                victim_piece=board[posn.y][posn.x];
                change_game_state(GameState::one_select_guess_or_attack);
            }
            else if (curr_piece_possibilities[i]
            .o_move_type==MoveType::attack) {
                game_state_=GameState::attacker_views_attacking;

                show_attack_matchup(posn);
            }
            else if (curr_piece_possibilities[i].o_move_type==MoveType::move) {

                move_piece(posn);
                change_game_state(GameState::pausing);
            }
        }
    }
    curr_piece_possibilities.clear();
}

void
Model::display_possibilities()
{
    std::vector<MoveOption> possibilities= {};
    Position curr_posn = curr_piece.p_posn;
    Position four_posns[4]={Position(-1,0),Position(1,0),
                            Position(0,-1),Position(0,1)};
    /// BOMB & FLAG
    if (curr_piece.p_type==-1 || curr_piece.p_type==11) {
        curr_piece_possibilities=possibilities;
    }
    else {
        /// MOVING PIECES
        for (int i=0;i<4;i++) {
            Position displace=four_posns[i];
            Position checking=Position(curr_posn.x+displace.x,curr_posn
                                                                      .y+displace.y);
            bool continue_for_2=true;
            while (continue_for_2) {
                if (checking.x>=0 && checking.x<10 &&
                     checking.y>=0 && checking.y<8) {
                    // if in bounds
                    if (turn == Turn::blue && board[checking.y][checking.x]
                                                      .p_team == Team::red) {
                        // if blue can attack red piece
                        possibilities.push_back(MoveOption{checking,
                                                           MoveType::attack});
                        continue_for_2 = false;
                    } else if (turn == Turn::red && board[checking.y][checking.x]
                                                            .p_team == Team::blue) {
                        // if red can attack blue piece
                        possibilities.push_back(MoveOption{checking,
                                                           MoveType::attack});
                        continue_for_2 = false;
                    } else if ((turn == Turn::blue && board[checking.y][checking
                    .x].p_team == Team::blue) || (turn == Turn::red &&
                    board[checking.y][checking.x].p_team == Team::red)){
                        continue_for_2 = false;
                    } else if (board[checking.y][checking
                            .x].p_team == Team::pit) {
                        continue_for_2 = false;
                    }
                    else {
                        // if either can move to empty space
                        possibilities.push_back(MoveOption{checking,
                                                           MoveType::move});
                        if (curr_piece.p_type==2) {
                            displace.x+=four_posns[i].x;
                            displace.y+=four_posns[i].y;
                            checking=Position(curr_posn.x+displace.x,
                                              curr_posn.y+displace.y);
                        }
                        else {
                            continue_for_2=false;
                        }
                    }
                }
                else {
                    continue_for_2=false;
                }
            }
        }
        curr_piece_possibilities=possibilities;
    }
}

void
Model::on_frame(double dt)
{

}
