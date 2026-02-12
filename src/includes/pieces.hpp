#pragma once

#include <cstdint>
#include <vector>

enum class piece_type : uint8_t {
    PAWN,
    KNIGHT,
    KING,
    QUEEN,
    ROOK,
    BISHOP,
};

// temporary
struct Position {
    int m_x; // number
    int m_y; // letter

    Position operator+(const Position& pos) const;
    bool     operator==(const Position& pos) const;
    bool     operator<(const Position& pos) const;
    // bool     operator>(const Position& pos) const;
};

struct Steps {
    int first_direction;
    int second_direction;
};

struct Piece {
    piece_type            type;
    bool                  is_white;
    char                  piece_representation;
    Position              initial_position;
    Position              current_position;
    std::vector<Position> get_moves() const;
};

std::vector<Position> move(Piece& piece, Position& position);