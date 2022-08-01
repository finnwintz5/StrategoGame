#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    void draw_background(ge211::Sprite_set& set);

    void draw_start(ge211::Sprite_set& set);
    void draw_game_over(ge211::Sprite_set& set);
    void draw_pause_screen(ge211::Sprite_set& set);
    void draw_viable_placing_spots(ge211::Sprite_set& set);
    void draw_matchup(ge211::Sprite_set& set);
    void draw_pieces(ge211::Sprite_set& set);
    void draw_all_pieces(ge211::Sprite_set& set);
    void draw_blank_pieces(ge211::Sprite_set& set);
    void draw_current(ge211::Sprite_set& set);
    void draw_possibilities(ge211::Sprite_set& set);
    void draw_offboard(ge211::Sprite_set& set);
    void draw_guessing(ge211::Sprite_set& set);
    void draw_forfeit(ge211::Sprite_set& set);
    void draw_guess_or_attack(ge211::Sprite_set& set);
    Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;
    int screen_to_board(int screen);
private:

    Model const& model_;
    // things to display
    ge211::Font font_0_;
    ge211::Font font_1_;
    ge211::Font font_2_;
    ge211::Font font_3_;
    ge211::Font font_3_2_;
    ge211::Font font_4_;
    ge211::Font font_5_;

    // OFFBOARD
    ge211::Rectangle_sprite highlighting_sprite;
    ge211::Rectangle_sprite viable_placing_spots;
    std::vector<ge211::Image_sprite> offboard_pieces_red_;
    std::vector<ge211::Image_sprite> offboard_pieces_blue_;
    std::vector<ge211::Text_sprite> offboard_subtext;
    ge211::Text_sprite current_text;
    ge211::Text_sprite select_text;
    ge211::Text_sprite guess_offboard_text;
    ge211::Text_sprite attack_offboard_text;
    ge211::Text_sprite pause_screen_text;
    ge211::Text_sprite forfeit_text;

    // Display possibilities
    ge211::Text_sprite attack_text;
    ge211::Text_sprite move_text;

    // other
    ge211::Text_sprite game_over;
    // background
    ge211::Image_sprite background_;
    ge211::Image_sprite stratego_logo_;
    ge211::Image_sprite red_blank_;
    ge211::Image_sprite blue_blank_;

};
