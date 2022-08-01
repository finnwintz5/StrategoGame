#pragma once

#include "model.hxx"
#include "view.hxx"

struct Controller : public ge211::Abstract_game
{
public:
    Controller();
    void temporary_prep_for_choosing();
protected:
    void draw(ge211::Sprite_set& set) override;
    void on_mouse_move(ge211::Posn<int> position) override;
    std::string initial_window_title() const override;
    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;
    void on_frame(double dt) override;
    void on_key(ge211::Key) override;
    View::Dimensions initial_window_dimensions() const override;
private:
    using Position = ge211::Posn<int>;
    Model model_;
    View view_;
    Position mouse_pos_;
    // music stuff
    //ge211::Music_track background_music_;
    //ge211::Sound_effect explosion_sound_;

};
