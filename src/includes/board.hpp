#pragma once
#include <array>
#include <random>
#include <vector>

struct Position {
    int x; //number
    int y; //letter

    bool operator==(const Position& B) const {return ((x == B.x) && (y == B.y));};
};

class Board {

    private :
    std::array<std::array<char,8>,8> m_lines;

    public:
    Board () {};
    void show_lines();
    bool square_is_empty(Position square){if (square.x != 8){return (m_lines[square.x][square.y]== ' ');} else {return false;}};
    void board_representation();
    void classic_start();
    const char * get_label(int line, int col) const;
    void updates_lines(Position start, Position end);

    std::vector <Position> get_squares_possible(Position test); //temporary fonction to teste
    bool square_colored(std::vector <Position> squares, Position square);

    // void transform_pawn();

};

bool piece_color (const char * label);



