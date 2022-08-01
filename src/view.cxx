#include "view.hxx"
#include <iostream>

// define sizes
static int const size_vert=71;
static int const size_hor=72;

std::vector<std::string>
p_sprites_create_red()
{
    std::vector<std::string> p_sprite_files_red;
    for (int i=-1;i<12;i++) {
        p_sprite_files_red.push_back("red-"+
                                  std::to_string(i) + ".png");
    }
    return p_sprite_files_red;
}

std::vector<std::string>
p_sprites_create_blue()
{
    std::vector<std::string> p_sprite_files_blue;
    for (int i=-1;i<12;i++) {
        p_sprite_files_blue.push_back("blue-"+
                                      std::to_string(i) + ".png");
    }
    return p_sprite_files_blue;
}


std::vector<ge211::Text_sprite>
offboard_subtext()
{
    std::vector<ge211::Text_sprite> offboard_text_sprites;
    for (int i=-1;i<12;i++) {
        offboard_text_sprites.push_back(ge211::Text_sprite());
    }
    return offboard_text_sprites;
}

static std::vector<std::string> p_sprites_files_red = p_sprites_create_red();
static std::vector<std::string> p_sprites_files_blue = p_sprites_create_blue();
static std::vector<ge211::Text_sprite> offboard_subtext_sprites =
        offboard_subtext();

View::View(Model const& model)
        : model_(model),
          font_0_("arcadeclassic.ttf",15),
          font_1_("arcadeclassic.ttf",17),
          font_2_("arcadeclassic.ttf",30),
          font_3_("arcadeclassic.ttf",35),
          font_3_2_("arcadeclassic.ttf",60),
          font_4_("arcadeclassic.ttf",70),
          font_5_("arcadeclassic.ttf",120),
          highlighting_sprite({66,61},
                              ge211::Color(0xFF,0xFF,0x00)),
          viable_placing_spots({708,200},
                               ge211::Color(0x38,0xA3,0x17)),
          offboard_pieces_red_(),
          offboard_pieces_blue_(),
          offboard_subtext(offboard_subtext_sprites),
          background_("board.png"),
          stratego_logo_("stratego.png"),
          red_blank_("red-blank.png"),
          blue_blank_("blue-blank.png")
{
    for(std::string const& filename : p_sprites_files_red) {
        offboard_pieces_red_.push_back(ge211::Image_sprite(filename));
    }
    for(std::string const& filename : p_sprites_files_blue) {
        offboard_pieces_blue_.push_back(ge211::Image_sprite(filename));
    }
}



int
View::screen_to_board(int screen)
{
    return screen/72;
}


void
View::draw_background(ge211::Sprite_set& set)
{
    set.add_sprite(background_,{0,-6},0);
}

void
View::draw_start(ge211::Sprite_set& set)
{
    set.add_sprite(stratego_logo_,{135,200},0);
    ge211::Text_sprite::Builder text_builder(font_3_);
    text_builder.color(ge211::Color(0xFF,0xFF,0xFF));
    text_builder << "click     to     start";
    game_over.reconfigure(text_builder);
    set.add_sprite(game_over,{230,400},1);
}

void
View::draw_viable_placing_spots(ge211::Sprite_set& set)
{
    ge211::Text_sprite::Builder text_builder(font_4_);
    text_builder.color(ge211::Color(0xFF,0xFF,0x00));
    text_builder << "place  pieces  here";
    game_over.reconfigure(text_builder);
    if (model_.get_turn()==Turn::red) {
        set.add_sprite(viable_placing_spots,{6,6},1);
        set.add_sprite(game_over,{50,80},4);
    } else if (model_.get_turn()==Turn::blue) {
        set.add_sprite(viable_placing_spots,{6,6+size_vert*5},1);
        set.add_sprite(game_over,{50,80+size_vert*5},4);
    }
}

void
View::draw_game_over(ge211::Sprite_set& set)
{
    ge211::Text_sprite::Builder text_builder2(font_5_);
    text_builder2.color(ge211::Color(0xFF,0xFF,0x00));
    if (model_.get_turn()==Turn::blue) {
        text_builder2 << "red wins";
        pause_screen_text.reconfigure(text_builder2);
        set.add_sprite(pause_screen_text,{120,580},4);
    }
    else if (model_.get_turn()==Turn::red) {
        text_builder2 << "blue wins";
        pause_screen_text.reconfigure(text_builder2);
        set.add_sprite(pause_screen_text,{90,580},4);

    }
}

void
View::draw_forfeit(ge211::Sprite_set& set)
{
    if (model_.get_turn()==Turn::red) {
        set.add_sprite(red_blank_,
                       {7+5*size_hor,7+9*size_vert},2);
    }
    else if (model_.get_turn()==Turn::blue) {
        set.add_sprite(blue_blank_,
                       {7+5*size_hor,7+9*size_vert},2);
    }
    ge211::Text_sprite::Builder text_builder(font_0_);
    text_builder.color(ge211::Color(0xFF,0xFF,0x00));
    text_builder << "forfeit";
    forfeit_text.reconfigure(text_builder);
    set.add_sprite(forfeit_text,{10+size_hor*5,23+size_vert*9},3);

    set.add_sprite(highlighting_sprite,{3+size_hor*5,
                                        3+size_vert*9},1);

}

void
View::draw_current(ge211::Sprite_set& set)
{

    if (model_.get_turn()==Turn::red) {
        if (model_.curr_piece.p_team==Team::red) {
            set.add_sprite(offboard_pieces_red_[model_.curr_piece.p_type+1],
                           {7+9*size_hor-10,7+9*size_vert},2);
        }
        else {
            set.add_sprite(red_blank_,
                           {7+9*size_hor-10,7+9*size_vert},2);
        }
    }
    else if (model_.get_turn()==Turn::blue) {
        if (model_.curr_piece.p_team==Team::blue) {
            set.add_sprite(offboard_pieces_blue_[model_.curr_piece.p_type+1],
                           {7+9*size_hor-10,7+9*size_vert},2);
        }
        else {
            set.add_sprite(blue_blank_,
                           {7+9*size_hor-10,7+9*size_vert},2);
        }
    }
    set.add_sprite(highlighting_sprite,{3+size_hor*9-10,
                                        3+size_vert*9},1);

    ge211::Text_sprite::Builder text_builder(font_3_);
    text_builder.color(ge211::Color(0xFF,0xFF,0x00));
    text_builder << "current";
    current_text.reconfigure(text_builder);
    set.add_sprite(current_text,{size_hor*7-10,12+size_vert*9},3);
}

void
View::draw_guess_or_attack(ge211::Sprite_set& set)
{
    // draw select text
    ge211::Text_sprite::Builder text_builder(font_2_);
    text_builder.color(ge211::Color(0xFF,0xFF,0x00));
    text_builder << "select";
    select_text.reconfigure(text_builder);
    set.add_sprite(select_text,{size_hor*1+24,size_vert*8-10},2);

    // draw guess text with blank box
    ge211::Text_sprite::Builder text_builder2(font_1_);
    text_builder2.color(ge211::Color(0xFF,0xFF,0x00));
    text_builder2 << "guess";
    guess_offboard_text.reconfigure(text_builder2);
    set.add_sprite(guess_offboard_text,{14+size_hor*1,24+size_vert*8},2);

    // draw attack text with blank box
    ge211::Text_sprite::Builder text_builder3(font_1_);
    text_builder3.color(ge211::Color(0xFF,0xFF,0x00));
    text_builder3 << "attack";
    attack_offboard_text.reconfigure(text_builder3);
    set.add_sprite(attack_offboard_text,{9+size_hor*2,24+size_vert*8},2);

    if (model_.get_turn()==Turn::blue) {
        set.add_sprite(red_blank_,{7+size_hor*1,7+size_vert*8},1);
        set.add_sprite(red_blank_,{7+size_hor*2,7+size_vert*8},1);
    }
    else if (model_.get_turn()==Turn::red) {
        set.add_sprite(blue_blank_,{7+size_hor*1,7+size_vert*8},1);
        set.add_sprite(blue_blank_,{7+size_hor*2,7+size_vert*8},1);
    }
}

void
View::draw_guessing(ge211::Sprite_set& set)
{
    for (int i=0;i<13;i++) {
        int row_num=0;
        int displace=0;
        if (i<10) {
            row_num=8;
        }
        else {
            row_num=9;
            displace=10;
        }
        ge211::Text_sprite::Builder text_builder(font_3_);
        text_builder.color(ge211::Color(0xFF,0xFF,0x00));

        //ge211::Image_sprite sprite = ge211::Image_sprite("red-blank.png");
        //Piece(model_.off_grid_row1[i],ge211::Posn<int>(0,0),Team::red).p_sprite;

        if (model_.get_turn()==Turn::red) {
            set.add_sprite(offboard_pieces_blue_[i],
                           {7+size_hor*(i-displace),7+size_vert*row_num},1);
        }
        else if (model_.get_turn()==Turn::blue) {
            set.add_sprite(offboard_pieces_red_[i],
                           {7+size_hor*(i-displace),7+size_vert*row_num},1);
        }
    }
}

void
View::draw_offboard(ge211::Sprite_set& set)
{
    for (int i=0;i<13;i++) {
        int row_num=0;
        int displace=0;
        if (i<10) {
            row_num=8;
        }
        else {
            row_num=9;
            displace=10;
        }
        ge211::Text_sprite::Builder text_builder(font_3_);
        text_builder.color(ge211::Color(0xFF,0xFF,0x00));

        //ge211::Image_sprite sprite = ge211::Image_sprite("red-blank.png");
        //Piece(model_.off_grid_row1[i],ge211::Posn<int>(0,0),Team::red).p_sprite;

        if (model_.get_turn()==Turn::red) {
            set.add_sprite(offboard_pieces_red_[i],
                           {7+size_hor*(i-displace),7+size_vert*row_num},1);
            text_builder << model_.get_red_unplaced_amount(i-1);
        }
        else if (model_.get_turn()==Turn::blue) {
            set.add_sprite(offboard_pieces_blue_[i],
                           {7+size_hor*(i-displace),7+size_vert*row_num},1);
            text_builder << model_.get_blue_unplaced_amount(i-1);
        }
        offboard_subtext[i].reconfigure(text_builder);
        set.add_sprite(offboard_subtext[i],{50+size_hor*(i-displace),
                                                -10+size_vert*row_num},2);
    }
}

void
View::draw_matchup(ge211::Sprite_set& set)
{
    int victimy=model_.victim_piece.p_posn.y;
    int victimx=model_.victim_piece.p_posn.x;

    set.add_sprite(model_.victim_piece.p_sprite,{7+size_hor*victimx,
                                                            7+size_vert*victimy},3);
    set.add_sprite(highlighting_sprite,{3+size_hor*victimx,
                                        3+size_vert*victimy},2);
    int attackery=model_.curr_piece.p_posn.y;
    int attackerx=model_.curr_piece.p_posn.x;
    set.add_sprite(model_.curr_piece.p_sprite,{7+size_hor*attackerx,
                                                            7+size_vert*attackery},3);
    set.add_sprite(highlighting_sprite,{3+size_hor*attackerx,
                                        3+size_vert*attackery},2);

    //click to see result text
    ge211::Text_sprite::Builder text_builder(font_3_2_);
    text_builder.color(ge211::Color(0xFF,0xFF,0x00));
    text_builder << "click  to  see  result";
    pause_screen_text.reconfigure(text_builder);
    set.add_sprite(pause_screen_text,{70,610},4);
}

void
View::draw_pause_screen(ge211::Sprite_set& set)
{
    ge211::Text_sprite::Builder text_builder(font_3_2_);
    text_builder.color(ge211::Color(0xFF,0xFF,0x00));
    if (model_.get_turn()==Turn::blue) {
        text_builder << "click  when  blue  ready";
    }
    else if (model_.get_turn()==Turn::red) {
        text_builder << "click  when  red  ready";
    }
    pause_screen_text.reconfigure(text_builder);
    set.add_sprite(pause_screen_text,{40,610},4);
    draw_blank_pieces(set);
}

void
View::draw_blank_pieces(ge211::Sprite_set& set)
{
    for (int i=0; i<8;i++) {
        for (int j=0; j<10;j++) {
            if(model_.board[i][j].p_team==Team::blue) {
                set.add_sprite(blue_blank_,{7+size_hor*j,7+size_vert*i},1);
            }
            else if (model_.board[i][j].p_team==Team::red) {
                set.add_sprite(red_blank_,{7+size_hor*j,7+size_vert*i},1);
            }
        }
    }
}

void
View::draw_all_pieces(ge211::Sprite_set& set)
{
    for (int i=0; i<8;i++) {
        for (int j=0; j<10;j++) {
            if(model_.board[i][j].p_team!=Team::none && model_.board[i][j]
                                                                .p_team!=Team::pit) {

                set.add_sprite(model_.board[i][j].p_sprite,{7+size_hor*j,
                                                            7+size_vert*i},1);

            }
        }
    }
}

void
View::draw_pieces(ge211::Sprite_set& set)
{
    for (int i=0; i<8;i++) {
        for (int j=0; j<10;j++) {
            if(model_.board[i][j].p_team!=Team::none && model_.board[i][j]
            .p_team!=Team::pit) {
                if (model_.get_turn()==Turn::blue && model_.board[i][j]
                .p_team==Team::red) {
                    // hide red square
                    set.add_sprite(red_blank_,{7+size_hor*j,7+size_vert*i},1);
                }
                else if (model_.get_turn()==Turn::red && model_.board[i][j]
                                                             .p_team==Team::blue) {
                    // hide blue square
                    set.add_sprite(blue_blank_,{7+size_hor*j,
                                                                7+size_vert*i},1);
                }
                else {
                    set.add_sprite(model_.board[i][j].p_sprite,{7+size_hor*j,
                                                                7+size_vert*i},1);
                }
            }
        }
    }
}

void
View::draw_possibilities(ge211::Sprite_set& set)
{
    ge211::Text_sprite::Builder text_builder(font_3_);
    text_builder.color(ge211::Color(0xFF,0xFF,0x00));
    if (model_.curr_piece.p_type==1) {
        text_builder << "A/G";
    }
    else {
        text_builder << "A";
    }

    attack_text.reconfigure(text_builder);
    ge211::Text_sprite::Builder text_builder2(font_3_);
    text_builder2 << "M";
    move_text.reconfigure(text_builder2);

    for (MoveOption const& possible : model_.curr_piece_possibilities) {
        if (possible.o_move_type==MoveType::attack) {
            if (model_.curr_piece.p_type==1) {
                set.add_sprite(attack_text,{9+size_hor*possible.o_posn.x,
                                            15+size_vert*possible.o_posn.y},2);
            }
            else {
                set.add_sprite(attack_text,{27+size_hor*possible.o_posn.x,
                                            15+size_vert*possible.o_posn.y},2);
            }
        }
        else if (possible.o_move_type==MoveType::move) {
            set.add_sprite(move_text,{27+size_hor*possible.o_posn.x,
                                      15+size_vert*possible.o_posn.y},2);
        }
    }
}

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return Dimensions(718,718);
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Stratego";
}