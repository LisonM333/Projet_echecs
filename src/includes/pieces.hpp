#pragma once
#include <vector>
#include <cstdint>
#include "../includes/types.hpp"

struct Position {
    int x; // number
    int y; // letter

    bool operator==(const Position& B) const { return ((x == B.x) && (y == B.y)); };

    bool operator<(const Position& B) const
    {
        if (x < B.x)
            return true;
        if (x > B.x)
            return false;
        return y < B.y;
    }
enum class piece_type : uint8_t {
    PAWN,
    KNIGHT,
    KING,
    QUEEN,
    ROOK,
    BISHOP,
};

struct Piece {
    piece_type            type;
    bool                  is_white;
    Position              initial_position;
    Position              current_position;
    std::vector<Position> get_moves() const;

    char representation() const;
};

std::vector<Position> move(Piece& piece, Position& position);