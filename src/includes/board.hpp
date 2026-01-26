#pragma once
#include <array>

class Board {

    private :
    std::array<std::array<char,8>,8> lines;

    public:
    Board () {};
    void board_representation();
    // void updates_lines();
    // void transform_pawn();

};