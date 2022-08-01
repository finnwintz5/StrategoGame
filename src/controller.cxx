#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_),
          mouse_pos_(ge211::Posn<int> {100,100})
{

}

void
Controller::draw(ge211::Sprite_set& set)
{
    if (model_.game_state()==GameState::start) {
        view_.draw_start(set);
    }
    else {
        view_.draw_background(set);
        view_.draw_possibilities(set);
        if (model_.game_state()==GameState::game_over) {
            view_.draw_game_over(set);
            view_.draw_all_pieces(set);
        }
        else if (model_.game_state()==GameState::pausing) {
            view_.draw_pause_screen(set);
        }
        else if (model_.game_state()==GameState::attacker_views_attacking ||
                 model_.game_state()==GameState::victim_views_attacking
                 || model_.game_state()==GameState::guessing_views_attacking){
            view_.draw_pieces(set);
            view_.draw_matchup(set);
        }
        else {
            view_.draw_pieces(set);
            view_.draw_current(set);
        }
        if (model_.game_state()==GameState::one_select_guess_or_attack) {
            view_.draw_guess_or_attack(set);
        }
        else if (model_.game_state()==GameState::placing) {
            view_.draw_offboard(set);
        }
        else if (model_.game_state()==GameState::guessing) {
            view_.draw_guessing(set);
        }
        else if (model_.game_state()==GameState::intro_placing) {
            view_.draw_viable_placing_spots(set);
        }
        if (model_.game_state()!=GameState::start &&
            model_.game_state()!=GameState::game_over &&
            model_.game_state()!=GameState::pausing &&
            model_.game_state()!=GameState::attacker_views_attacking &&
            model_.game_state()!=GameState::victim_views_attacking &&
            model_.game_state()!=GameState::guessing_views_attacking) {
            view_.draw_forfeit(set);
        }
    }


}

void
Controller::on_frame(double dt)
{

}

void
Controller::temporary_prep_for_choosing()
{
    ///RED
    //Flag
    model_.place_or_set_to_place(Position(0,8));
    model_.place_or_set_to_place(Position(0,0));
    //Spy
    model_.place_or_set_to_place(Position(1,8));
    model_.place_or_set_to_place(Position(1,0));
    //1
    model_.place_or_set_to_place(Position(2,8));
    model_.place_or_set_to_place(Position(2,0));
    model_.place_or_set_to_place(Position(3,0));
    //2
    model_.place_or_set_to_place(Position(3,8));
    model_.place_or_set_to_place(Position(5,2));
    model_.place_or_set_to_place(Position(6,2));
    model_.place_or_set_to_place(Position(7,2));
    model_.place_or_set_to_place(Position(7,0));
    model_.place_or_set_to_place(Position(8,0));
    //3
    model_.place_or_set_to_place(Position(4,8));
    model_.place_or_set_to_place(Position(9,0));
    model_.place_or_set_to_place(Position(9,1));
    model_.place_or_set_to_place(Position(8,1));
    model_.place_or_set_to_place(Position(5,1));
    model_.place_or_set_to_place(Position(4,1));
    //4
    model_.place_or_set_to_place(Position(5,8));
    model_.place_or_set_to_place(Position(7,1));
    model_.place_or_set_to_place(Position(6,1));
    //5
    model_.place_or_set_to_place(Position(6,8));
    model_.place_or_set_to_place(Position(3,1));
    model_.place_or_set_to_place(Position(2,1));
    //6
    model_.place_or_set_to_place(Position(7,8));
    model_.place_or_set_to_place(Position(1,1));
    model_.place_or_set_to_place(Position(0,1));
    //7
    model_.place_or_set_to_place(Position(8,8));
    model_.place_or_set_to_place(Position(0,2));
    //8
    model_.place_or_set_to_place(Position(9,8));
    model_.place_or_set_to_place(Position(1,2));
    //9
    model_.place_or_set_to_place(Position(0,9));
    model_.place_or_set_to_place(Position(2,2));
    //10
    model_.place_or_set_to_place(Position(1,9));
    model_.place_or_set_to_place(Position(3,2));
    //Bomb
    model_.place_or_set_to_place(Position(2,9));
    model_.place_or_set_to_place(Position(4,2));
    model_.place_or_set_to_place(Position(4,0));
    model_.place_or_set_to_place(Position(5,0));
    model_.place_or_set_to_place(Position(6,0));
    model_.place_or_set_to_place(Position(8,2));
    model_.place_or_set_to_place(Position(9,2));
    // place blue
    model_.place_or_set_to_place(Position(0,8));
    model_.place_or_set_to_place(Position(0,7));
    model_.place_or_set_to_place(Position(1,8));
    model_.place_or_set_to_place(Position(1,7));
    model_.place_or_set_to_place(Position(2,8));
    model_.place_or_set_to_place(Position(2,7));
    model_.place_or_set_to_place(Position(3,7));
    model_.place_or_set_to_place(Position(3,8));
    model_.place_or_set_to_place(Position(4,7));
    model_.place_or_set_to_place(Position(5,7));
    model_.place_or_set_to_place(Position(6,7));
    model_.place_or_set_to_place(Position(7,7));
    model_.place_or_set_to_place(Position(8,7));
    model_.place_or_set_to_place(Position(4,8));
    model_.place_or_set_to_place(Position(9,7));
    model_.place_or_set_to_place(Position(9,6));
    model_.place_or_set_to_place(Position(8,6));
    model_.place_or_set_to_place(Position(7,6));
    model_.place_or_set_to_place(Position(6,6));
    model_.place_or_set_to_place(Position(5,8));
    model_.place_or_set_to_place(Position(5,6));
    model_.place_or_set_to_place(Position(4,6));
    model_.place_or_set_to_place(Position(6,8));
    model_.place_or_set_to_place(Position(3,6));
    model_.place_or_set_to_place(Position(2,6));
    model_.place_or_set_to_place(Position(7,8));
    model_.place_or_set_to_place(Position(1,6));
    model_.place_or_set_to_place(Position(0,6));
    model_.place_or_set_to_place(Position(8,8));
    model_.place_or_set_to_place(Position(0,5));
    model_.place_or_set_to_place(Position(9,8));
    model_.place_or_set_to_place(Position(1,5));
    model_.place_or_set_to_place(Position(0,9));
    model_.place_or_set_to_place(Position(2,5));
    model_.place_or_set_to_place(Position(1,9));
    model_.place_or_set_to_place(Position(3,5));
    model_.place_or_set_to_place(Position(2,9));
    model_.place_or_set_to_place(Position(4,5));
    model_.place_or_set_to_place(Position(5,5));
    model_.place_or_set_to_place(Position(6,5));
    model_.place_or_set_to_place(Position(7,5));
    model_.place_or_set_to_place(Position(8,5));
    model_.place_or_set_to_place(Position(9,5));
}

void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int>)
{

    ge211::Posn<int> mouse_in_grid = {view_.screen_to_board(mouse_pos_.x),
                                      view_.screen_to_board(mouse_pos_.y)};
    // PLACING
    if (mouse_in_grid.x==5 && mouse_in_grid.y==9 &&
            model_.game_state()!=GameState::start &&
            model_.game_state()!=GameState::game_over &&
            model_.game_state()!=GameState::pausing &&
            model_.game_state()!=GameState::attacker_views_attacking &&
            model_.game_state()!=GameState::victim_views_attacking &&
            model_.game_state()!=GameState::guessing_views_attacking) {
        model_.change_game_state(GameState::game_over);
    }
    if (model_.game_state()==GameState::start) {
        model_.change_game_state(GameState::intro_placing);
    }
    else if (model_.game_state()==GameState::intro_placing) {
        model_.change_game_state(GameState::placing);
    }
    else if (model_.game_state()==GameState::placing) {
        //temporary_prep_for_choosing();
        model_.place_or_set_to_place(mouse_in_grid);
    }
    else if (model_.game_state()==GameState::guessing) {
        model_.guess_piece(mouse_in_grid);
    }
    else if (model_.game_state()==GameState::one_select_guess_or_attack) {
        model_.guess_or_attack(mouse_in_grid);
    }
    else if (model_.game_state()==GameState::choosing) {
        model_.act_or_set_new_act(mouse_in_grid);
    }
    else if (model_.game_state()==GameState::pausing) {
        // just click changes to playing & changes turn
        if (model_.attacking_must_be_shown_to_victim) {
            model_.change_game_state(GameState::victim_views_attacking);
            model_.attacking_must_be_shown_to_victim=false;
        } else {
            model_.change_game_state(GameState::choosing);
        }
    }
    else if (model_.game_state()==GameState::guessing_views_attacking) {
        model_.change_game_state(GameState::pausing);
    }
    else if (model_.game_state()==GameState::attacker_views_attacking) {
        model_.attack_piece();
    }
    else if (model_.game_state()==GameState::victim_views_attacking) {
        model_.change_game_state(GameState::choosing);
    }
}

void
Controller::on_mouse_move(ge211::Posn<int> position)
{
    mouse_pos_ = position;
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        //quit();
    }

}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}
