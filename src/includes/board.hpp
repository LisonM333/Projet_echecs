#pragma once
#include <array>
#include <imgui.h>
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
    void show_lines() const;

    void square_representation(const int& line,const int& colum, const char*& label, const ImVec4& colo_case, const ImVec4& colo_piece, bool& selected) const;
    void board_representation();
    void classic_start();
    void move_gestion(std::pair<Position,Position>& move, std::vector<Position>& list);

    const char * get_label(const int& line,const int& colum) const;
    bool square_colored(const std::vector<Position>& squares,const Position& square) const;
    bool get_piece_color (const char *& label) const;
    bool square_is_empty(const Position& square) const {if (square.x != 8){return (m_lines[square.x][square.y]== ' ');} else {return false;}};

    std::vector <Position> get_squares_possible(const Position& position) const;//temporary function to test
    void updates_lines(const Position& start, const Position& end);
    
    // void transform_pawn();

};





