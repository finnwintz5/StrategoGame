#include <ge211.hxx>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Game_config {
public:
    //
    // HELPFUL TYPE ALIASES
    //

    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;
public:
    // CONSTRUCTORS
    Game_config();
    // PUBLIC DATA MEMBERS
    int counter_left; //x value
    int counter_right; // x value

    int top_counter; // y value

    int bottom_counter;

    std::vector<int> counter_y_posns; // y values

    Dimensions scene_dims;
};
