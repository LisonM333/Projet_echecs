#pragma once
#include <array>

class Board {

    private :
    std::array<std::array<char,8>,8> m_lines;

    public:
    Board () {};
    void board_representation();
    void classic_start();
    const char * get_label(int line, int col) const;
    // void updates_lines();
    // void transform_pawn();

};

bool piece_color (const char * label);