#pragma once
#include <ge211.hxx>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/// PIECE TYPE KEY
// -1=flag
// 0=spy
// 1=spotter
// 2=scout
// 3=miner
// 4,5,6,7,8,9=not special
// 10=marshall
// 11=bomb

enum class Team
{
    blue,
    red,
    pit,
    none
};

class Piece
{
public:
    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;
    // CONSTRUCTORS
    Piece(int,Position,Team);
public:
    /// PUBLIC MEMBER VARIABLES
    int p_type;
    Position p_posn; // x value is x position, y value is y position
    Team p_team;
    ge211::Image_sprite p_sprite;

    // PUBLIC FUNCTIONS
    // function to move the bartender to whatever counter is written

    // ge211::Posn<int> {config.counter_end,config
    // .counter_y_posns[1]}
};