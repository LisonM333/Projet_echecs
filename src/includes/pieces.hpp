#pragma once
#include <vector>
#include "../includes/types.hpp"
#include "../includes/board.hpp"

struct Piece {
    piece_type            type;
    bool                  is_white;
    Position              initial_position;
    Position              current_position;
    std::vector<Position> get_moves() const;

    char representation() const;
};

std::vector<Position> move(Piece& piece, Position& position);