#pragma once
#include <cstdint>

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
};