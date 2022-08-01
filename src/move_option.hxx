#pragma once
#include <ge211.hxx>
#include <iostream>
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



class MoveOption
{
public:
    using Position = ge211::Posn<int>;

    Position o_posn;
    MoveType o_move_type;
    MoveOption(Position,MoveType);

};