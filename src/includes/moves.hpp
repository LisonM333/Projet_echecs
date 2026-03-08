#pragma once

#include <vector>
#include "../includes/types.hpp"

// apply relative moves to an absolute position on the board
std::vector<Position> apply_relative_moves(const std::vector<Position>& relative_moves, const Position& position);

// get relative moves for each type
std::vector<Position> get_pawn_relative_moves();
std::vector<Position> get_knight_relative_moves();
std::vector<Position> get_bishop_relative_moves();
std::vector<Position> get_rook_relative_moves();
std::vector<Position> get_king_relative_moves();
std::vector<Position> get_queen_relative_moves();

// get relative move for one piece type
std::vector<Position> get_relative_moves(const piece_type& type);
